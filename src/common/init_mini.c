/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/10 16:30:04 by glaguyon         ###   ########.fr       */
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
	rl_outstream = stderr;
	rl_event_hook = &event;
	mini->exc = 0;
	mini->forked = 0;
	mini->newpipe[0] = -1;
	mini->newpipe[1] = -1;
	mini->oldpipe[0] = -1;
	mini->oldpipe[1] = -1;
	mini->pids = NULL;
	if (isatty(0))
		mini->prompt = "coquillage de petite taille > ";
	else
		mini->prompt = NULL;
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}
