/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:13:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/30 18:49:59 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//toutes les parentheses et op doivent disparaitre

//pb si signe puis parenthese..
t_tree	*build_tree(t_list **lbuild, int *err, int *exc)
{
	t_list	*curr;
	t_tok	*tok;

	curr = *lbuild;
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == PAR)
			//prio
		else if (tok->tok == OP)
			//arbre
		else
			//pipeline
	}
	return	(NULL);
}
