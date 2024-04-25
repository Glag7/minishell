/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/25 19:00:39 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	update_pwd_oldpwd(char **envp, char *cwd)
{
	char	**pwd;
	char	*new_var;

	pwd = get_var(envp, "PWD");
	if (pwd == NULL && get_var(envp, "OLDPWD") == NULL)
		return (0);
	if (pwd == NULL && get_var(envp, "OLDPWD") != NULL)
	{
		remove_var(envp, "OLDPWD", free);
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
}*/

//si PWD ou OLDPWD a ete unset elle doit etre recree par cd mais plus affichee ni par export ni par env -> utiliser un char static dans une fonction accedee a la fois par env, export et cd
static char	update_cd_envp(char **envp, char *new_oldpwd)
{
	char	*new_pwd;
	int		error;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		error = chdir(new_oldpwd);
		if (error != 0)
			perror(strerror(errno));
		return (1);
	}
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

static char	*get_absolute_path(char *arg)
{
	char	*pathanme;
	char	*cwd;

	pathname = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	pathname = ft_strappend(pathname, "/", 1);
	if (pathname == NULL)
		return (NULL);
	pathname = ft_strappend(pathname, arg, 1);
	return (pathname);
}

static char	change_directory(char **envp, char *pathname)
{
	int		error;
	char	*new_oldpwd;

	new_oldpwd = getcwd(NULL, 0);
	if (new_oldpwd == NULL)
	{
		free(pathname);
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	error = chdir(pathname);
	free(pathname);
	if (error != 0)
	{
		free(new_oldpwd);
		perror(strerror(errno));
		return ((int)errno);
	}
	if (update_cd_envp(envp, new_oldpwd) == 1)
	{
		free(new_oldpwd);
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	return (0);
}

int	builtin_cd(int argc, char **argv, char **envp)
{
	char	*pathname;

	if (check_envp(argc, envp, argv) != 0)
		return (1);
	if (argc <= 1)
		pathname = ft_strdup(&((*get_var(envp, "HOME"))[5]));
	else if (ft_strncmp(argv[1], "-", -1) == 0)
		pathname = ft_strdup(&(*get_var(envp, "OLDPWD"))[7]);
	else if (argv[1][0] == '~')
		pathname = get_absolute_path(argv[1]);
	else
		pathname = ft_strdup(argv[1]);
	if (pathanme == NULL)
	{
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		return (2);
	}
	if (ft_strncmp(argv[1], "-", -1) == 0
		&& (write(1, pathname, ft_strlen(pathname)) == -1
			|| write(1, "\n", 1) == -1))
	{
		free(pathname);
		return (1);
	}
	return (change_directory(envp, pathname));
}
