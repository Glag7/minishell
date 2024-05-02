/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:55:31 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/02 19:50:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pars(t_list *pars)
{
	t_tok	*tok;
	ssize_t	plevel;

	plevel = 0;
	while (pars)
	{
		tok = (t_tok *)pars->content;
		if (tok->tok == PAR)
		{
			plevel += (tok->type == OPEN) - (tok->type == CLOSE);
			if (plevel < 0)
				return (1);
			if (pars->next && ((t_tok *)pars->next->content)->tok == PAR
				&& ((t_tok *)pars->next->content)->type != tok->type)
				return (1);
		}
		pars = pars->next;
	}
	return (plevel != 0);
}
