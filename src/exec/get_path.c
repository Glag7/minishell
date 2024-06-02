/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:22:18 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/02 17:28:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_err(t_mini *mini, int *err, int res)
{
	if (res != ENOENT)
		*err = res;
	if (mini->err == ERR_AINTNOWAY || res == 0)
		return (1);
	return (0);
}

static int	try_path(t_mini *mini, char *path, char *cmd, char **dst)
{
	struct stat	stat;

	path = ft_strjoin(path, "/");
	if (path == NULL)
		mini->err = ERR_AINTNOWAY;
	if (path == NULL)
		return (1);
	cmd = ft_strjoin(path, cmd);
	free(path);
	if (cmd == NULL)
		mini->err = ERR_AINTNOWAY;
	if (cmd == NULL)
		return (1);
	if (access(cmd, X_OK) == 0 && !lstat(cmd, &stat))
	{
		if (S_ISDIR(stat.st_mode))
			free(cmd);
		if (S_ISDIR(stat.st_mode))
			return (EISDIR);
		*dst = cmd;
		return (0);
	}
	free(cmd);
	return (errno);
}

static int	srch_path(t_mini *mini, char **cmd, char **dst, char *path)
{
	char	**pathes;
	size_t	i;
	int		err;

	pathes = ft_split(path, ':');
	if (pathes == NULL)
		mini->err = ERR_AINTNOWAY;
	if (pathes == NULL)
		return (1);
	i = 0;
	err = ENOENT;
	while (pathes[i])
	{
		if (assign_err(mini, &err,
				try_path(mini, pathes[i], cmd[0], dst)))
			break ;
		i++;
	}
	if (mini->err != ERR_AINTNOWAY && err)
		get_path_err(mini, err, cmd[0]);
	ft_freearr(pathes);
	return (*dst == NULL);
}

static int	srch_absolute(t_mini *mini, char **cmd, char **dst)
{
	int			err;
	struct stat	stat;

	if (access(cmd[0], X_OK) || lstat(cmd[0], &stat))
	{
		err = errno;
		ft_perror3("minishell: ", cmd[0], ": ");
		ft_perror3(strerror(err), "\n", "");
		if (err == ENOENT)
			mini->exc = 127;
		else
			mini->exc = 126;
		return (1);
	}
	if (S_ISDIR(stat.st_mode))
	{
		ft_perror3("minishell: ", cmd[0], ": ");
		ft_perror3(strerror(EISDIR), "\n", "");
		mini->exc = 126;
		return (1);
	}
	*dst = ft_strdup(cmd[0]);
	if (*dst == NULL)
		mini->err = ERR_AINTNOWAY;
	return (*dst == NULL);
}

int	get_path(t_mini *mini, char **cmd, char **dst)
{
	t_str	path;

	if (!cmd[0])
		return (1);
	if (!cmd[0][0])
	{
		ft_perror("minishell: '': command not found\n");
		mini->exc = 127;
		return (1);
	}
	if (ft_strncmp(cmd[0], ".", -1) == 0 || ft_strncmp(cmd[0], "..", -1) == 0)
	{
		ft_perror3("minishell: ", cmd[0], ": command not found\n");
		mini->exc = 127;
		return (1);
	}
	path = varchr((t_str){"PATH", 4}, mini->envp.envp, mini);
	if (ft_strchr(cmd[0], '/') || path.len == 0)
		return (srch_absolute(mini, cmd, dst));
	return (srch_path(mini, cmd, dst, path.s));
}
