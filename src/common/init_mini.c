/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/08 18:25:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (0);
}

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	rl_event_hook = &event;
	mini->exc = 0;
	mini->forked = 0;
	mini->pids = NULL;
	if (isatty(0))
		mini->prompt = "coquillage de petite taille > ";
	else
		mini->prompt = NULL;
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}
