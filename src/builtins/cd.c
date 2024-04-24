/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/24 19:37:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	update_pwd_oldpwd(char **envp, char *cwd)
{
	char	**pwd;
	char	*new_var;

	pwd = get_var(envp, "PWD");
	if (pwd == NULL && get_var(envp, "OLDPWD") == NULL)
		return (0);
	if (pwd == NULL && get_var(envp, "OLDPWD") != NULL)
	{
		remove_var(envp, "OLDPWD");
		return (0);
	}
	new_var = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (new_var == NULL)
		return (1);
	replace_var(envp, new_var, "OLDPWD");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	new_var = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (new_var == NULL)
		return (1);
	replace_var(envp, new_var, "PWD");
	return (0);
}

static char	check_envp(int argc, char **envp, char **argv)
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

static char	parse_cd(char **pathname_ptr)
{
	char	*cwd;
	char	*pathname;
	char	*absolute_pathname;

	pathname = *pathname_ptr;
	if (pathname[0] != '~')
		return (0);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (1);
	}
	absolute_pathname = ft_strappend(cwd, "/", 1);
	if (absolute_pathname == NULL)
		return (1);
	absolute_pathname = ft_strappend(absolute_pathname, pathname, 1);
	if (absolute_pathname == NULL)
		return (1);
	free(pathname);
	*pathname_ptr = absolute_pathname;
	return (0);
}

static char	change_directory(char **envp, char *pathname)
{
	int		error;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	error = chdir(pathname);
	if (error != 0)
	{
		perror(strerror(errno));
		return ((int)errno);
	}
	if (update_pwd_oldpwd(envp, cwd) == 1)
	{
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	return (0);
}

int	builtin_cd(int argc, char **argv, char **envp)//tester deletion de OLDPWD si pas de PWD entre autres
{
	char	*pathname;

	if (check_envp(argc, envp, argv) != 0)
		return (1);
	if (argc <= 1)
		pathname = &((*get_var(envp, "HOME"))[5]);
	else if (parse_cd(&argv[1]))
		return (2);
	else if (ft_strncmp(argv[1], "-", -1) == 0)
	{
		pathname = &(*get_var(envp, "OLDPWD"))[7];
		if (write(1, pathname, ft_strlen(pathname)) == -1)
			return (2);
	}
	else
		pathname = argv[1];
	return (change_directory(envp, pathname));
}
