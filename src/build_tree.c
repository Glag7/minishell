/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:13:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/01 14:17:47 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//toutes les parentheses et op et pipes doivent disparaitre
//recursion sur && || | (

t_tree	*build_tree(t_list **lbuild, t_clean *garbage, int *err, int *exc);
{
	t_list	*head;

	head = *lbuild;
	while (head)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == PAR && tok->type == OPEN)
			//prio
		else if (tok->tok == OP)
			//arbre
		else if (tok->tok == PIPE)
			//pipeline
	}
	return	(NULL);
}
