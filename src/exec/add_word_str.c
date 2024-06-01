/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:54:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/01 16:11:28 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_word_len(t_list *curr)
{
	t_tok	*tok;
	size_t	len;
	size_t	i;

	len = 0;
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == VAR || (tok->tok == UNDEF && tok->quote.qtype))
			len += tok->quote.str.len;
		else if (tok->tok == UNDEF)
		{
			i = -1;
			while (++i < tok->quote.str.len
				&& ft_in(tok->quote.str.s[i], " \t\n") == -1)
				len++;
			if (i < tok->quote.str.len)
				break ;
		}
		else
			break ;
		curr = curr->next;
	}
	return (len);
}

static void	copy_strings(t_list **lst, t_list *curr, t_str s)
{
	size_t	off;
	t_tok	*tok;

	off = 0;
	while (s.len - off > 0)
	{
		tok = (t_tok *)curr->content;
		if (tok->quote.str.len < s.len - off || tok->tok == VAR)
		{
			ft_memcpy(s.s + off, tok->quote.str.s, tok->quote.str.len);
			off += tok->quote.str.len;
		}
		else
		{
			ft_memcpy(s.s + off, tok->quote.str.s, s.len - off);
			tok->quote.str.s += s.len - off;
			tok->quote.str.len -= s.len - off;
			if (tok->quote.qtype == 0)
				break ;
			off = s.len;
		}
		curr = curr->next;
	}
	*lst = curr;
}

static void	skip_empty(t_list **lst, t_list *curr)
{
	while (curr && ((t_tok *)curr->content)->tok == UNDEF
		&& ((t_tok *)curr->content)->quote.str.len == 0)
		curr = curr->next;
	*lst = curr;
}

int	add_word_str(t_mini *mini, t_list **lst, t_list *curr)
{
	t_str	s;

	s.len = get_word_len(*lst);
	s.s = malloc(s.len + 1);
	if (s.s == NULL)
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		return (2);
	}
	*((t_tok *)curr->content) = (t_tok){TXT, .s = s};
	if (s.len)
		copy_strings(lst, *lst, s);
	skip_empty(lst, *lst);
	s.s[s.len] = 0;
	return (0);
}
