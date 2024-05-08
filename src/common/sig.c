/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:12:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 18:42:06 by glaguyon         ###   ########.fr       */
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

static void	handle_hdoc(int sig)
{
	g_sig = sig;
	printf("\001\033[%dC\002^C", (int) ft_strlen(rl_prompt) + rl_point);
	rl_replace_line("", 0);
	rl_done = 1;
}

void	sig_mode(int mode)
{
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
