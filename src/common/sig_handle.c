/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:09 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/31 15:54:40 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

void	handle_inter(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		ft_perror("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_hdoc(int sig)
{
	g_sig = sig;
	ft_perror("^C");
	rl_replace_line("", 0);
	rl_done = 1;
}

void	handle_builtin(int sig)
{
	g_sig = sig;
}
