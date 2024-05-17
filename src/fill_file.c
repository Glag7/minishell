/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:22:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/17 23:17:34 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static int	end_loop(char *s, t_str lim)
{
	if (g_sig == SIGINT)
	{
		free(s);
		return (128 + SIGINT);
	}
	if (s == NULL)
	{
		ft_perror3("minishell: warning: heredoc delimited by EOF (wanted '",
			lim.s, "')\n");
		return (0);
	}
	return (0);
}

static int	get_input(t_mini *mini, int fd, t_str lim)
{
	char	*s;
	size_t	len;

	while (1)
	{
		s = readline(mini->hprompt);
		if (g_sig == SIGINT || s == NULL)
			return (end_loop(s, lim));
		if (ft_strncmp(lim.s, s, -1) == 0)
			break ;
		len = ft_strlen(s);
		s[len] = '\n';
		if (write(fd, s, len + 1) == -1)
		{
			ft_perror3("minishell: heredoc: ", strerror(errno), "\n");
			free(s);
			return (2);
		}
		free(s);
	}
	free(s);
	return (0);
}

static int	do_hdoc(int fd, t_mini *mini, t_str lim)
{
	int	res;

	sig_mode(SIG_HDOC);
	mini->exc = 0;
	mini->err = ERR_SHUTUP;
	mini->forked = 1;
	res = get_input(mini, fd, lim);
	sig_mode(SIG_IGNORE);
	close(fd);
	if (res)
	{
		ft_lstclear(&mini->hdocs, &wrap_unlink);
		mini->exc = res;
		return (1);
	}
	return (1);
}

int	fill_file(int fd, t_str lim, t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_perror3("minishell: fork: ", strerror(errno), "\n");
		close(fd);
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
		return (1);
	}
	else if (pid == 0)
		return (do_hdoc(fd, mini, lim));
	waitpid(pid, &status, 0);
	sig_mode(SIG_INTER);
	mini->exc = WEXITSTATUS(status);
	close(fd);
	return (mini->forked || mini->exc);
}
