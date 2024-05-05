/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 17:19:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

static void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\001\033[%dC\002^C\n", (int) ft_strlen(rl_prompt) + rl_point);
		g_sig = sig;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	signal(SIGINT, &sig_handle);
	signal(SIGQUIT, &sig_handle);
	show_ctl(0);
	mini->exc = 0;
	mini->forked = 0;
	if (isatty(0))
		mini->prompt = "coquillage de petite taille > ";
	else
		mini->prompt = NULL;
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp){envp, 1, 1};
}
