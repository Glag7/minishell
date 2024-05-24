/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wdcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:26:26 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/24 18:13:15 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_len(t_list *curr)
{
	t_tok	*tok;
	size_t	len;

	len = 0;
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == WDCARD)
			len++;
		else if (tok->tok == TXT)
			len += tok->s.len;
		else
			break ;
	}
	return (len);
}

static void	copy_wdtxt(t_str s, t_list *curr)
{
	t_tok	*tok;
	size_t	off;

	off = 0;
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == WDCARD)
		{
			s.s[off] = '*';
			off++;
		}
		else if (tok->tok == TXT)
		{
			ft_memcpy(s.s + off, tok->s.s, tok->s.len);
			off += tok->s.len;
		}
		else
			break ;
	}
	s.s[s.len] = 0;
}

static int	add_wdtxt(t_list **files, t_list *curr)
{
	t_tok	*tok;

	tok = malloc(sizeof(*tok));
	*files = ft_lstnew(tok);
	if (*files == NULL || tok == NULL)
	{
		free(tok);
		free(*files);
		return (1);
	}
	tok->tok = TXT;
	tok->s.len = get_len(curr);
	tok->s.s = malloc(tok->s.len + 1);
	if (tok->s.s == NULL)
	{
		free(tok);
		free(*files);
		return (1);
	}
	copy_wdtxt(tok->s, curr);
	return (0);
}

static int	replace_wdcard(t_mini *mini, t_list **replace,
	t_list *curr, t_str *fnames)
{
	t_list	*files;

	files = NULL;
	while (fnames->s)
	{
		if (add_wdname(&files, curr))
		{
			ft_lstclear(&files, &free_lexec);
			mini->err = ERR_AINTNOWAY;
			mini->exc = 2;
			return (1);
		}
		fnames++;
	}
	if (files == NULL && add_wdtxt(&files, curr))
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		return (1);
	}
	ft_lstadd_back(&files, free_wdcard(curr));
	*replace = files;
	return (0);
}

int	exp_wdcard(t_mini *mini, t_list **lst, t_str *fnames)
{
	t_list	*curr;

	if (((t_tok *)(*lst)->content)->tok == UNDEF)
		ft_lstpop(lst, &free, 1);
	if (((*lst && ((t_tok *)(*lst)->content)->tok == WDCARD)
		|| (*lst && (*lst)->next && ((t_tok *)(*lst)->content)->tok == TXT
		&& ((t_tok *)(*lst)->next->content)->tok == WDCARD))
		&& replace_wdcard(mini, lst, *lst, fnames))
		return (1);
	curr = *lst;
	while (curr)
	{
		if (((curr->next && ((t_tok *)curr->next->content)->tok == WDCARD)
				|| (curr->next && curr->next->next
					&& ((t_tok *)curr->next->content)->tok == TXT
					&& ((t_tok *)curr->next->next->content)->tok == WDCARD))
			&& replace_wdcard(mini, &curr->next, curr->next, fnames))
			return (1);
		curr = curr->next;
	}
	return (0);
}
