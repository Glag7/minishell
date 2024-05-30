/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/28 19:06:18 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_envp(int argc, char **envp, char **argv)
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

static char	*get_savepoint(char *pathname)
{
	char	*savepoint;

	savepoint = getcwd(NULL, 0);
	if (savepoint == NULL)
	{
		free(pathname);
		ft_perror("minishell: cd: getcwd(): malloc(): failed memory \
			allocation\n");
		return (NULL);
	}
	return (savepoint);
}

static int	change_directory(t_envp *envp_status, char *pathname)
{
	int		error;
	char	*savepoint;

	savepoint = get_savepoint(pathname);
	if (savepoint == NULL)
		return (2);
	error = chdir(pathname);
	free(pathname);
	if (error != 0)
	{
		free(savepoint);
		error = errno;
		ft_perror("minishell: cd: chdir(): ");
		perror(strerror(error));
		return (1);
	}
	if (update_cd_envp(envp_status) == 1)
	{
		chdir(savepoint);
		free(savepoint);
		ft_perror("minishell: cd: malloc(): failed memory allocation\n");
		return (2);
	}
	free(savepoint);
	return (0);
}

int	builtin_cd(int argc, char **argv, t_envp *envp_status, int *fds)
{
	char	*pathname;

	if (check_envp(argc, envp_status->envp, argv) != 0)
		return (1);
	if (argc <= 1)
		pathname = ft_strdup(&(*get_var(envp_status->envp, "HOME"))[5]);
	else if (ft_strncmp(argv[1], "-", -1) == 0)
		pathname = ft_strdup(&(*get_var(envp_status->envp, "OLDPWD"))[7]);
	else if (argv[1][0] == '~')
		pathname = get_absolute_path(argv[1]);
	else
		pathname = ft_strdup(argv[1]);
	if (pathname == NULL)
	{
		ft_perror("minishell: cd: malloc(): failed memory allocation\n");
		return (2);
	}
	if (argc > 1 && ft_strncmp(argv[1], "-", -1) == 0
		&& (write(fds[WRITE], pathname, ft_strlen(pathname)) == -1
			|| write(fds[WRITE], "\n", 1) == -1))
	{
		free(pathname);
		return (1);
	}
	return (change_directory(envp_status, pathname));
}
