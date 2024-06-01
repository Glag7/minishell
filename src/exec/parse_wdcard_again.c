/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wdcard_again.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:25:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/01 17:04:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	add_remaining(t_list *curr, t_tok *tok, size_t i)
{
	t_list	*tmp;
	t_tok	*tmptok;

	if (tok->quote.str.len - i - 1)
	{
		tmptok = malloc(sizeof(*tmptok));
		tmp = ft_lstnew(tmptok);
		if (tmptok == NULL || tmp == NULL)
		{
			free(tmptok);
			free(tmp);
			return (1);
		}
		*tmptok = (t_tok){.tok = UNDEF, .quote = (t_quote){0, (t_str){
			tok->quote.str.s + i + 1,
			tok->quote.str.len - i - 1}}};
		ft_lstinsert(&curr, tmp, 0);
	}
	return (0);
}

static int	add_wdcard(t_list *curr, t_tok *tok, size_t i)
{
	t_list	*tmp;

	if (add_remaining(curr, tok, i))
		return (1);
	tok->quote.str.len = i;
	if (i != 0)
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tok == NULL || tmp == NULL)
		{
			free(tok);
			free(tmp);
			return (1);
		}
		ft_lstinsert(&curr, tmp, 0);
	}
	*tok = (t_tok){.tok = WDCARD};
	return (0);
}

static int	search_wdcard(t_list *curr)
{
	t_tok	*tok;
	size_t	i;

	i = 0;
	tok = (t_tok *)curr->content;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '*')
			return (add_wdcard(curr, tok, i));
		i++;
	}
	return (0);
}

int	parse_wdcard_again(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0
			&& search_wdcard(tmp))
		{
			*err = ERR_AINTNOWAY;
			*exc = 2;
			ft_lstclear(lst, &free_lbuild);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
