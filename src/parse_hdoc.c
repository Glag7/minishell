/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:13:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/24 16:54:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_prev(t_list **curr, t_tok **tok)
{
	t_list	*tmp;

	*tok = malloc(sizeof(**tok));
	tmp = ft_lstnew(tok);
	if (*tok == NULL || tmp == NULL)
	{
		free(*tok);
		free(tmp);
		return (ERR_AINTNOWAY);
	}
	ft_lstinsert(curr, tmp, 0);
	return (0);
}

static int	add_lim(t_list *lst, t_tok *tok, size_t i, t_str *lim)
{
	size_t	size;
	t_list	*tmp;

	lim->s = malloc(lim->len + 1);
	if (lim->s == NULL)
		return (ERR_AINTNOWAY);
	size = ft_min(lim->len, tok->quote.str.len - i);
	ft_memcpy(lim->s, tok->quote.str.s + i, size);
	if (i + lim->len < tok->quote.str.len)
	{
		if (add_prev(&lst, &tok))
			return (ERR_AINTNOWAY);
		*tok = (t_tok){.tok = UNDEF, .quote = {.qtype = 0, .str = {((t_tok *)
				lst->content)->quote.str.s + i + lim->len, ((t_tok *)
				lst->content)->quote.str.len - i - lim->len}}};
	}
	lst = lst->next;
	while (size < lim->len)
	{
		size += ft_min(lim->len, tok->quote.str.len - i);
		ft_memcpy(lim->s, tok->quote.str.s + i, ft_min(lim->len, tok->quote.str.len - i));
		tmp = lst->next;
		ft_lstpop(&lst, &free, 0);
		lst = tmp;
	}
	return (0);
}

static int	search_lim(t_list *lst, t_tok *tok, size_t i, t_hdoc *hdoc)
{
	t_list	*tmp;
	size_t	j;

	tmp = lst;
	while (i < tok->quote.str.len && ft_in(tok->quote.str.s[i], " \t\n") != -1)
		i++;
	while (tmp && j < tok->quote.str.len)
	{
		tok = (t_tok *)tmp->content;
		hdoc->expand &= (tok->quote.qtype) == 0;
		if (tok->quote.qtype)
			hdoc->lim.len += tok->quote.str.len;
		else
		{
			j = i;
			while (j < tok->quote.str.len
				&& ft_in(tok->quote.str.s[j], " \t\n") != -1)
				j++;
			hdoc->lim.len += j;
			i = 0;
		}
		tmp = tmp->next;
	}
	tok = (t_tok *)lst->content;
	return (add_lim(lst, tok, i, &hdoc->lim));
}

static int	search_hdoc(t_list *curr, t_list *tmp, t_tok *tok)
{
	size_t	i;
	t_hdoc	hdoc;
	int		err;

	i = -1;
	hdoc = (t_hdoc){.expand = 1, .lim = (t_str){NULL, 0}};
	while (++i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '<' && tok->quote.str.s[i + 1] == '<')
		{
			err = search_lim(tmp, tok, i + 2, &hdoc);
			if (err == ERR_AINTNOWAY)
				free(hdoc.lim.s);
			tok->quote.str.len = i;
			if (err == 0 && i != 0)
				err = add_prev(&curr, &tok);
			if (err == 0)
				*tok = (t_tok){.tok = HDOC, .hdoc = hdoc};
			if (err == ERR_AINTNOWAY)
				free(hdoc.lim.s);
			return (err);
		}
	}
	return (0);
}

void	parse_hdoc(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;
	int		res;

	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0)
		{
			res = search_hdoc(tmp, tmp, ((t_tok *)tmp->content));
			if (res)
			{
				if (res == ERR_AINTNOWAY)
					*err = ERR_AINTNOWAY;
				else
					ft_perror(MSG_HDOC);
				*exc = 2;
				ft_lstclear(lst, &free_lbuild);
			}
			return ;
		}
		tmp = tmp->next;
	}
}
