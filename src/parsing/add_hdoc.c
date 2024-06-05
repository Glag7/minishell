/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:03:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/05 14:01:04 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_loop(t_list *lst, t_list *curr, t_str *lim, size_t size)
{
	t_list	*tmp;
	t_tok	*tok;

	if (size > lim->len)
	{
		tok = (t_tok *)curr->content;
		tok->quote.str.s += tok->quote.str.len - (size - lim->len);
		tok->quote.str.len = size - lim->len;
		tmp = curr;
	}
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (!(tok->tok == UNDEF && tok->quote.str.len == 0))
			break ;
		tmp = curr->next;
		ft_lstdelone(curr, &free);
		curr = tmp;
	}
	lst->next = tmp;
	lim->s[lim->len] = 0;
}

static int	add_lim(t_list *lst, t_tok *tok, size_t i, t_str *lim)
{
	size_t	size;
	t_list	*tmp;
	t_list	*curr;

	lim->s = malloc(lim->len + 1);
	if (lim->s == NULL)
		return (ERR_AINTNOWAY);
	size = 0;
	ft_memcpy(lim->s, tok->quote.str.s + i, size);
	curr = lst->next;
	while (size < lim->len)
	{
		tok = (t_tok *)curr->content;
		ft_memcpy(lim->s + size, tok->quote.str.s,
			ft_min(lim->len - size, tok->quote.str.len));
		size += tok->quote.str.len;
		if (size <= lim->len)
		{
			tmp = curr->next;
			ft_lstdelone(curr, &free);
			curr = tmp;
		}
	}
	end_loop(lst, curr, lim, size);
	return (0);
}

static int	add_unquoted(t_hdoc *hdoc, t_tok *tok, size_t i, bool offset)
{
	size_t	j;

	if (offset)
		j = i;
	else
		j = 0;
	while (j < tok->quote.str.len
		&& ft_in(tok->quote.str.s[j], " \t\n<>") == -1)
		j++;
	if (offset)
		hdoc->lim.len += j - i;
	else
		hdoc->lim.len += j;
	if (j < tok->quote.str.len)
		return (1);
	return (0);
}

int	search_lim(t_list *lst, t_tok *tok, size_t i, t_hdoc *hdoc)
{
	t_list	*tmp;

	tmp = lst;
	while (i < tok->quote.str.len
		&& ft_in(tok->quote.str.s[i], " \t\n") != -1)
		i++;
	if (i >= tok->quote.str.len)
		tmp = tmp->next;
	while (tmp && ((t_tok *)tmp->content)->tok == UNDEF)
	{
		tok = (t_tok *)tmp->content;
		hdoc->expand &= (tok->quote.qtype) == 0;
		if (tok->quote.qtype)
			hdoc->lim.len += tok->quote.str.len;
		else if (add_unquoted(hdoc, tok, i, (tmp == lst)))
			break ;
		tmp = tmp->next;
	}
	if (hdoc->lim.len == 0 && hdoc->expand == 1)
		return (ERR_AINTNOWAY + 12345);
	tok = (t_tok *)lst->content;
	return (add_lim(lst, tok, i, &hdoc->lim));
}
