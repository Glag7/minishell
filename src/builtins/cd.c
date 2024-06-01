/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/01 13:50:30 by ttrave           ###   ########.fr       */
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
		ft_perror3(strerror(errno), "\n", "");
		free(pathname);
		return (1);
	}
	free(pathname);
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

int	builtin_cd(size_t argc, char **argv, t_envp *envp_status, int *fds)
{
	char	*pathname;

	if (check_envp(argc, envp_status->envp, argv) != 0)
		return (1);
	if (argc <= 1)
		pathname = ft_strdup(&(*get_var(envp_status->envp, "HOME"))[5]);
	else if (ft_strncmp(argv[1], "-", -1) == 0)
		pathname = ft_strdup(&(*get_var(envp_status->envp, "OLDPWD"))[7]);
	else if (ft_strncmp(argv[1], "~", -1) == 0)
		pathname = ft_strjoin("./", argv[1]);
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
