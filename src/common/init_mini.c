/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/17 14:29:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*foo(const char *var1, int var2)
{
	(void) var1;
	(void) var2;
	return (NULL);
}

static int	event(void)
{
	return (0);
}

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	rl_catch_signals = 0;
	rl_outstream = stderr;
	mini->exc = 0;
	mini->forked = 0;
	mini->newpipe[0] = -1;
	mini->newpipe[1] = -1;
	mini->oldpipe[0] = -1;
	mini->oldpipe[1] = -1;
	mini->pids = NULL;
	if (isatty(0))
	{
		mini->prompt = "coquillage de petite taille > ";
		rl_event_hook = &event;
	}
	else
	{
		rl_completion_entry_function = &foo;
		mini->prompt = NULL;
	}
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}
