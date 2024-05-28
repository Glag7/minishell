/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:22:18 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/28 19:25:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_path()
{
	tmp = ft_strjoin(pathes[i++]);
	if (tmp == NULL)
		mini->err = ERR_AINTNOWAY;
	if (tmp == NULL)
		return (1);

	free(tmp);
}

static int	srch_path(t_mini *mini, char **cmd, char **dst, char *path)
{
	char	**pathes;
	size_t	i;
	int		err;
	int		olderr;

	pathes = ft_split(path, ':');
	if (pathes == NULL)
		mini->err = ERR_AINTNOWAY;
	if (pathes == NULL)
		return (1);
	i = 0;
	while (pathes[i])//FIXME
	{
		err = try_path(mini, pathes[i]);
		if (err)
			olderr = err;
		if (err == -1)
			break ;
	}
	ft_freearr(pathes);
	if (err == 0)
	return (mini->err == ERR_AINTNOWAY ||);
}

static int	srch_absolute(t_mini *mini, char **cmd, char **dst)
{
	int	err;

	if (access(cmd[0], X_OK))
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
	*dst = ft_strdup(cmd[0]);
	if (*dst == NULL)
		mini->err = ERR_AINTNOWAY;
	return (*dst = NULL);
}

int	get_path(t_mini *mini, char **cmd, char **dst)
{
	t_str	path;

	if (!cmd[0])
		return (1);
	path = varchr((t_str){"PATH", 4}, mini->envp.envp, mini);
	if (ft_strchr('/', cmd[0]) || path.len == 0)
		return (srch_absolute(mini, cmd, dst));
	return (srch_path(mini, cmd, dst, path.s));
}