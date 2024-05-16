/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:12:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/16 23:56:19 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static void	show_ctl(bool show)
{
	struct termios	termios_data;

	tcgetattr(0, &termios_data);
	if (show)
		termios_data.c_lflag |= ECHOCTL;
	else
		termios_data.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_data);
}

static void	handle_inter(int sig)
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

static void	handle_hdoc(int sig)
{
	g_sig = sig;
	ft_perror("^C");
	rl_replace_line("", 0);
	rl_done = 1;
}

void	sig_mode(int mode)
{
	return ;
	if (mode == SIG_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		show_ctl(0);
	}
	else if (mode == SIG_INTER)
	{
		signal(SIGINT, &handle_inter);
		signal(SIGQUIT, &handle_inter);
		show_ctl(0);
	}
	else if (mode == SIG_HDOC)
	{
		signal(SIGINT, &handle_hdoc);
		signal(SIGQUIT, &handle_inter);
		show_ctl(0);
	}
	else if (mode == SIG_EXEC)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		show_ctl(1);
	}
}
