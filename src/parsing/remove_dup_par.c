/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dup_par.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:23:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/02 18:20:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(void *tok_);
void	check_remove_dup(t_list **lst, t_list **curr)
{
	ssize_t	plevel;
	t_list	*tmp;
	t_tok	*tok;

	tmp = (*curr)->next;
	plevel = 0;
	while (tmp)
	{
		tok = (t_tok *)tmp->content;
		if (tok->tok == PAR)
			plevel += (tok->type == OPEN) - (tok->type == CLOSE);
		if (plevel == 0)
		{
			if (((t_tok *)tmp->next->content)->tok == PAR)
			{
				ft_lstpop(curr, &free, 1);
				ft_lstpop(&(tmp->next), &free, 1);
				return ;
			}
			else
				break ;
		}
		tmp = tmp->next;
	}
	*curr = (*curr)->next;
}

void	remove_dup_par(t_list **lst)
{
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		if (((t_tok *)curr->content)->tok == PAR
			&& ((t_tok *)curr->content)->type == OPEN)
		{
			while (((t_tok *)curr->next->content)->tok == PAR
				&& ((t_tok *)curr->next->content)->type == OPEN)
				check_remove_dup(lst, &(curr->next));
			curr = curr->next;
		}
		else
			curr = curr->next;
	}
}
