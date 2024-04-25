/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:39:58 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:21 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_after(t_list *lst, t_tok *tok, size_t i, size_t len)
{
	t_list	*tmp;
	t_tok	*tmptok;

	if (i + len >= tok->quote.str.len)
		return (0);
	tmptok = malloc(sizeof(*tmptok));
	tmp = ft_lstnew(tmptok);
	if (tmptok == NULL || tmp == NULL)
	{
		free(tmptok);
		free(tmp);
		return (1);
	}
	ft_lstinsert(&lst, tmp, 0);
	*tmptok = (t_tok){UNDEF, .quote = {tok->quote.qtype,
		.str = {tok->quote.str.s + i + len, tok->quote.str.len - i - len}}};
	return (0);
}

static int	add_var(t_list *lst, t_tok *tok, size_t i, size_t len)
{
	t_list	*tmp;
	t_str	s;

	if (add_after(lst, tok, i, len))
		return (1);
	s = (t_str){malloc(len + 1), len};
	if (s.s)
		ft_memcpy(s.s, ((t_tok *)lst->content)->quote.str.s + i, len);
	tok->quote.str.len = i - 1;
	if (i > 1 || s.s == NULL)
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tok == NULL || tmp == NULL || s.s == NULL)
		{
			free(tok);
			free(tmp);
			free(s.s);
			return (1);
		}
		ft_lstinsert(&lst, tmp, 0);
	}
	s.s[len] = 0;
	*tok = (t_tok){VAR, .var = {((t_tok *)lst->content)->quote.qtype, s}};
	return (0);
}

static int	search_var(t_list *lst, t_tok *tok)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '$')
		{
			if (tok->quote.str.s[i + 1] == '?')
				return (add_var(lst, tok, i + 1, 1));
			while (i + len + 1 < tok->quote.str.len
				&& (ft_is(ALNUM, tok->quote.str.s[i + len + 1])
					|| tok->quote.str.s[i + len + 1] == '_'))
				len++;
			if (len)
				return (add_var(lst, tok, i + 1, len));
		}
		i++;
	}
	return (0);
}

void	parse_var(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;
	t_tok	*tok;

	tmp = *lst;
	while (tmp)
	{
		tok = ((t_tok *)tmp->content);
		if (tok->tok == UNDEF && tok->quote.qtype != QUOTE)
		{
			if (search_var(tmp, tok))
			{
				*err = ERR_AINTNOWAY;
				*exc = 2;
				ft_lstclear(lst, &free_lbuild);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
