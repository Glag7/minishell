/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:22:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 14:32:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error(int err)
{
	ft_perror("minishell: heredoc: ");
	ft_perror(strerror(err));
	ft_perror("\n");
}

static int	get_input(int fd, t_str lim)
{
	char	*s;
	size_t	len;

	while (1)
	{
		s = readline("hdoc > ");
		if (s == NULL)
		{
			ft_perror("minishell: warning: heredocument delimited by EOF (wanted '");
			ft_perror(lim.s);
			ft_perror("')\n");
			break ;
		}
		if (ft_strncmp(lim.s, s, -1) == 0)
			break ;
		len = ft_strlen(s);
		s[len] = '\n';
		if (write(fd, s, len + 1) == -1)
		{
			put_error(errno);
			return (1);
		}
		free(s);
	}
	free(s);
	return (0);
}

int	fill_file(int fd, t_str lim, t_mini *mini)
{
	int		tmperr;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		tmperr = errno;
		ft_perror("minishell: fork: ");
		ft_perror(strerror(tmperr));
		ft_perror("\n");
		close(fd);
		ft_lstclear(&mini->hdocs, &wrap_unlink);
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
		return (1);
	}
	else if (pid == 0)
	{
		mini->exc = 0;
		mini->err = ERR_SHUTUP; 
		mini->forked = 1;
		if (get_input(fd, lim))
		{
			close(fd);
			ft_lstclear(&mini->hdocs, &wrap_unlink);
			mini->exc = 2;
			return (1);
		}
	}
	else
		waitpid(pid, 0, 0);//signaux + exitcode
	close(fd);
	return (0);
}
