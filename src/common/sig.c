/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:12:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/31 15:54:44 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_ctl(bool show)
{
	struct termios	termios_data;

	if (!isatty(0))
		return ;
	tcgetattr(0, &termios_data);
	if (show)
		termios_data.c_lflag |= ECHOCTL;
	else
		termios_data.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_data);
}

void	sig_mode_more(int mode)
{
	if (mode == SIG_BUILTIN)
	{
		signal(SIGINT, &handle_builtin);
		signal(SIGQUIT, SIG_IGN);
		return (show_ctl(1));
	}
}

void	sig_mode(int mode)
{
	if (mode == SIG_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		return (show_ctl(0));
	}
	if (mode == SIG_INTER)
	{
		signal(SIGINT, &handle_inter);
		signal(SIGQUIT, &handle_inter);
		return (show_ctl(0));
	}
	if (mode == SIG_HDOC)
	{
		signal(SIGINT, &handle_hdoc);
		signal(SIGQUIT, &handle_inter);
		return (show_ctl(0));
	}
	if (mode == SIG_EXEC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (show_ctl(1));
	}
	return (sig_mode_more(mode));
}
