/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:54:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/23 15:10:55 by glaguyon         ###   ########.fr       */
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
		if (tok->tok == VAR || (tok->tok == UNDEF && tok->qtype))
			len += tok->quote.str.len;
		else if (tok->tok == UNDEF)
		{
			i = -1;
			while (++i < tok->quote.str.len
				&& ft_in(tok->quote.str.s[i], " \t\n") != -1)
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

int	add_word_str(t_mini *mini, t_list **lst, t_list **words)
{
	t_str	s;

	s.len = get_word_len(*lst);
	s.s = malloc(s.len + 1);
	return (0);
}
