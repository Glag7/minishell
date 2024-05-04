/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:22:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 20:44:21 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_input(int fd, t_str lim)
{
	char	*s;
	size_t	len;

	while (1)
	{
		s = readline("hdoc > ");
		if (s == NULL)
		{
			ft_perror("eof wanted blah blah\n");
			break ;
		}
		if (ft_strncmp(lim.s, s, -1) == 0)
			break ;
		len = ft_strlen(s);
		s[len] = '\n';
		write(fd, s, len + 1);
		free(s);
	}
	return (0);
}

int	fill_file(int fd, t_str lim, t_mini *mini)
{
	int		tmperr;
	pid_t	pid;

	if (fd == -1)
	{
		mini->exc = 2;
		ft_lstclear(&mini->hdocs, &wrap_unlink);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{//?
		tmperr = errno;
		close(fd);
		ft_perror("minishell: fork: ");
		ft_perror(strerror(tmperr));
		ft_perror("\n");
		mini->err = ERR_SHUTUP; 
	}
	else if (pid == 0)
	{
		mini->forked = 1;
		if (get_input(fd, lim))
			return (1);//ratio !!
	}
	else
		waitpid(pid, 0, 0);//signaux
	close(fd);
	if (mini->forked)
	{
		mini->exc = 0;
		mini->err = ERR_SHUTUP; 
	}
	return (0);
}
