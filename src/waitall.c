/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:24:38 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/08 20:22:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sig(int status)
{
	static char	*msg[] = {"", "Hangup", "", "Quit", "Illegal instruction",
		"Trace/breakpoint trap", "Aborted", "Bus error",
		"Floating point exception", "Killed", "User defined signal 1",
		"Segmentation fault", "User defined signal 2", "", "Alarm clock",
		"Terminated", "Stack fault", "", "", "Stopped", "Stopped", "Stopped",
		"Stopped", "", "CPU time limit exceeded", "File size limit exceeded",
		"Virtual timer expired", "Profiling timer expired", "",
		"I/O possible", "Power failure", "Bad system call"};
	int			sig;

	sig = WTERMSIG(status);
	if (sig < 32)
		ft_perror(msg[sig]);
	else if (sig == 32 || sig == 33)
		ft_perror("Unknown signal ");
	if (sig == 32 || sig == 33)
		ft_putnbr_fd(sig, 2);
	if (sig > 33 && sig < 64)
		ft_perror("Real-time signal ");
	if (sig > 33 && sig < 64)
		ft_putnbr_fd(sig - 35, 2);
	if (WCOREDUMP(status))
		ft_perror(" (core dumped)");
	if (sig != 13 && sig != 28 && )
		ft_perror("\n");
}

void	waitall(t_mini *mini)
{
	int	status;

	while (mini->pid)
	{
		if (waitpid(mini->pid->num, &status, 0) == -1)
		{
			ft_lstpop(&mini->pid, NULL, 1);
			continue ;
		}
		if ((mini->err == 0 || mini->err == ERR_BYEBYE) && WIFEXITED(status))
			mini->exc = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			print_sig(status);
		ft_lstpop(&mini->pid, NULL, 1);
	}
}
