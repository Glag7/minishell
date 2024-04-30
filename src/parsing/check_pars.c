/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:55:31 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/21 17:00:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pars(t_list *pars, ssize_t plevel)
{
	size_t	i;
	bool	notempty;
	bool	past_par;

	past_par = OPEN;
	while (pars && plevel == 0)
	{
		if (((t_tok *)pars->content)->tok == PAR)
		{
			if (past_par != ((t_tok *)pars->content)->type && !notempty)
				return (1);
			notempty = 0;
			past_par = ((t_tok *)pars->content)->type;
		}
		else
		{
			notempty = !!(((t_tok *)pars->content)->quote.qtype);
			i = -1;
			while (++i < ((t_tok *)pars->content)->quote.str.len && !notempty)
				notempty |= (ft_in(((t_tok *)pars->content)
							->quote.str.s[i], " \t\n") == -1);
		}
		pars = pars->next;
	}
	return (plevel != 0);
}
