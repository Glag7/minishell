/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/31 14:35:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (0);
}

#ifdef STUPID_TESTER

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	rl_catch_signals = 0;
	mini->exc = 0;
	mini->forked = 0;
	mini->newpipe[0] = -1;
	mini->newpipe[1] = -1;
	mini->oldpipe[0] = -1;
	mini->oldpipe[1] = -1;
	mini->pids = NULL;
	mini->hprompt = "icidocument > ";
	mini->prompt = "coquillage de petite taille > ";
	if (isatty(0))
		rl_event_hook = &event;
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}

#else

static char	*foo(const char *var1, int var2)
{
	(void) var1;
	(void) var2;
	return (NULL);
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
		mini->hprompt = "icidocument > ";
		mini->prompt = "coquillage de petite taille > ";
		rl_event_hook = &event;
	}
	else
	{
		mini->hprompt = NULL;
		rl_completion_entry_function = &foo;
		mini->prompt = NULL;
	}
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}

#endif
