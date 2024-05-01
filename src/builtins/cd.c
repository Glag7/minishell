/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/01 14:08:23 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_envp(int argc, char **envp, char **argv)
{
	if (argc >= 3)
	{
		ft_perror("minishell: cd: too many arguments\n");
		return (1);
	}
	if (argc <= 1 && (get_var(envp, "HOME") == NULL
			|| *get_var(envp, "HOME")[4] == '\0'))
	{
		ft_perror("minishell: cd: HOME not set\n");
		return (1);
	}
	if (argc > 1 && ft_strncmp(argv[1], "-", -1) == 0
		&& (get_var(envp, "OLDPWD") == NULL
			|| *get_var(envp, "OLDPWD")[6] == '\0'))
	{
		ft_perror("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	return (0);
}

static char	*get_absolute_path(char *arg)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (pathname == NULL)
		return (NULL);
	pathname = ft_strappend(pathname, "/", 1);
	if (pathname == NULL)
		return (NULL);
	pathname = ft_strappend(pathname, arg, 1);
	return (pathname);
}

static char	change_directory(t_envp *envp_status, char *pathname,
		char *savepoint_cwd, int error)
{
	savepoint_cwd = getcwd(NULL, 0);
	if (savepoint_cwd == NULL)
	{
		free(pathname);
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	error = chdir(pathname);
	free(pathname);
	if (error != 0)
	{
		free(savepoint_cwd);
		perror(strerror(errno));
		return (1);
	}
	if (update_cd_envp(envp_status) == 1)
	{
		chdir(savepoint_cwd);
		free(savepoint_cwd);
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	free(savepoint_cwd);
	return (0);
}

int	builtin_cd(int argc, char **argv, t_envp *envp_status)
{
	char	*pathname;

	if (check_envp(argc, envp_status->envp, argv) != 0)
		return (1);
	if (argc <= 1)
		pathname = ft_strdup(&((*get_var(envp_status->envp, "HOME"))[5]));
	else if (ft_strncmp(argv[1], "-", -1) == 0)
		pathname = ft_strdup(&(*get_var(envp_status->envp, "OLDPWD"))[7]);
	else if (argv[1][0] == '~')
		pathname = get_absolute_path(argv[1]);
	else
		pathname = ft_strdup(argv[1]);
	if (pathname == NULL)
	{
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	if (argc > 1 && ft_strncmp(argv[1], "-", -1) == 0
		&& (write(1, pathname, ft_strlen(pathname)) == -1
			|| write(1, "\n", 1) == -1))
	{
		free(pathname);
		return (1);
	}
	return (change_directory(envp_status, pathname, NULL, 0));
}
