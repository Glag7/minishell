/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/01 18:18:59 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_envp(size_t argc, char **envp, char **argv)
{
	char	**var;

	if (argc >= 3)
	{
		ft_perror("minishell: cd: too many arguments\n");
		return (1);
	}
	var = get_var(envp, "HOME");
	if (argc <= 1 && (var == NULL || (*var)[4] == '\0'))
	{
		ft_perror("minishell: cd: HOME not set\n");
		return (1);
	}
	var = get_var(envp, "OLDPWD");
	if (argc > 1 && ft_strncmp(argv[1], "-", -1) == 0
		&& (var == NULL || (*var)[6] == '\0'))
	{
		ft_perror("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	return (0);
}

static char	*get_savepoint(char *pathname, int *error)
{
	char	*savepoint;

	*error = 0;
	savepoint = getcwd(NULL, 0);
	if (savepoint == NULL)
	{
		if (errno == ENOENT)
			*error = 1;
		else
		{
			free(pathname);
			ft_perror("minishell: cd: getcwd(): malloc(): failed memory \
allocation\n");
		}
	}
	return (savepoint);
}

static int	change_directory(t_envp *envp_status, char *pathname)
{
	int		error;
	char	*savepoint;

	savepoint = get_savepoint(pathname, &error);
	if (savepoint == NULL && error != 1)
		return (2);
	if (pathname[0] != '\0' && chdir(pathname) != 0)
	{
		free(savepoint);
		savepoint = strerror(errno);
		ft_perror3("minishell: cd: ", pathname, ": ");
		ft_perror3(savepoint, "\n", "");
		free(pathname);
		return (1);
	}
	free(pathname);
	error = update_cd_envp(envp_status);
	if (error != 0 && savepoint != NULL)
		chdir(savepoint);
	free(savepoint);
	return (error);
}

static char	*alloc_pathname(size_t argc, char **argv, char **envp)
{
	char	*pathname;

	if (argc <= 1)
		pathname = ft_strdup(&(*get_var(envp, "HOME"))[5]);
	else if (ft_strncmp(argv[1], "-", -1) == 0)
		pathname = ft_strdup(&(*get_var(envp, "OLDPWD"))[7]);
	else if (ft_strncmp(argv[1], "~", -1) == 0)
		pathname = ft_strjoin("./", argv[1]);
	else
		pathname = ft_strdup(argv[1]);
	if (pathname == NULL)
		ft_perror("minishell: cd: malloc(): failed memory allocation\n");
	return (pathname);
}

int	builtin_cd(size_t argc, char **argv, t_envp *envp_status, int *fds)
{
	char	*pathname;
	char	**oldpwd;

	if (check_envp(argc, envp_status->envp, argv) != 0)
		return (1);
	pathname = alloc_pathname(argc, argv, envp_status->envp);
	if (pathname == NULL)
		return (2);
	oldpwd = get_var(envp_status->envp, "OLDPWD");
	if (argc > 1 && ft_strncmp(argv[1], "-", -1) == 0 && oldpwd != NULL
		&& (*oldpwd)[6] != '\0'
		&& ((*oldpwd)[7] == '\0' || access(&(*oldpwd)[7], X_OK) == 0)
		&& (ft_print("cd", fds[WRITE], pathname, ft_strlen(pathname)) == -1
			|| ft_print("cd", fds[WRITE], "\n", 1) == -1))
	{
		free(pathname);
		return (1);
	}
	return (change_directory(envp_status, pathname));
}
