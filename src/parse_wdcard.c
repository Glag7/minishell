/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wdcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:25:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/25 18:45:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_wdcard(t_list *lst, t_list **last_split,
		t_tok *tok, size_t offset)
{
	*last_split = lst->next;//un truc comme ca 
	return (0);
}

static int	search_wdcard(t_list *lst, t_list **last_split, t_tok *tok)
{
	size_t	i;
	size_t	lastspace;
	t_tok	*tmptok;

	i = -1;
	while (++i < tok->quote.str.len)
	{
		if (ft_in(tok->quote.str.s[i], " \t\n") != -1)
		{
			*last_split = lst;
			if (i == tok->quote.str.len)
				*last_split = (*last_split)->next;
		}
		else if (tok->quote.str.s[i] == '*')
		{
			i = -1;
			lastspace = 0;
			tmptok = ((t_tok *)(*last_split)->content);
			while (++i < tmptok->quote.str.len)
				if (ft_in(tmptok->quote.str.s[i], " \t\n") != -1)
					lastspace = i + 1;
			return (add_wdcard(lst, last_split, tmptok, lastspace));
		}
	}
}

void	parse_wdcard(t_list **lst, int *err, int *exc)
{
	t_list	*curr;
	t_list	*last_split;
	t_tok	*tok;

	curr = *lst;
	last_split = curr;
	while (curr)
	{
		tok = ((t_tok *)curr->content);
		if (tok->tok != UNDEF && tok->tok != VAR)
			last_split = curr->next;
		else if (tok->quote.qtype == 0
			&& search_wdcard(curr, &last_split, tok))
		{
			*exc = 2;
			*err = ERR_AINTNOWAY;
			ft_lstclear(lst, &free_lbuild);
			return ;
		}
		curr = curr->next;
	}
}
