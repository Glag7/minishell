/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:13:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/26 19:16:39 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	insert_pwd_oldpwd(char **new_envp, char **old_envp, char *new_pwd, char *new_oldpwd)
{
	size_t	i;
	char	*pwd;
	char	*oldpwd;
	char	**old_pwd;
	char	**old_oldpwd;

	pwd = ft_strjoin("PWD=", new_pwd);
	if (new_oldpwd != NULL)
		oldpwd = ft_strjoin("OLDPWD=", new_oldpwd);
	else
		oldpwd = ft_strdup("OLDPWD");
	if (pwd == NULL || oldpwd == NULL)
	{
		free(pwd);
		free(oldpwd);
		return (1);
	}
	// suite, copier envp et remplacer / append a la fin
	return (0);
}

//si new_oldpwd == NULL, creer/ecraser/laisser OLDPWD pas init, sinon creer/ecraser/laisser OLDPWD avec OLDPWD=new_oldpwd
//creer/ecraser/laisser PWD avec PWD=new_pwd
static bool	update_cd_pwd_oldpwd(char ***envp, char *new_pwd, char **new_oldpwd_ptr)
{
	char	**new_envp;
	char	*new_oldpwd;
	char	**old_envp;
	size_t	len;

	old_envp = *envp;
	len = (get_var(old_envp, "PWD") == NULL) + (get_var(old_envp, "OLDPWD") == NULL);
	while (old_envp[len] != NULL)
		len++;
	new_envp = malloc((len + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	new_envp[len] = NULL;
	new_oldpwd = NULL;
	if (new_oldpwd_ptr != NULL)
		new_oldpwd = &(*new_oldpwd_ptr)[len_until_char(*new_oldpwd_ptr, '=') + 1];
	if (insert_pwd_oldpwd(new_envp, old_envp, new_pwd, new_oldpwd) == 1)
	{
		free(new_envp);
		return (1);
	}
	// concat PWD= + new_envp et inserer dans new_envp
	// si new_oldpwd == NULL : inserer OLDPWD, sinon : concat OLDPWD= + new_oldpwd et inserer dans new_envp
	free(old_envp);
	*envp = new_envp;
	return (0);
}

// si PWD ou OLDPWD a ete supprime par unset il doit etre recree
// PWD contient le cwd
// OLDPWD contient le contenu de l'ancien PWD, si celui-ci n'existait pas, OLDPWD est declare et pas initialise
static bool	update_cd_envp(t_envp *envp_status)
{
	char	*new_pwd;
	char	**new_oldpwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
		return (1);
	new_oldpwd = get_var(envp_status->envp, "PWD");
	if (new_oldpwd != NULL && (*new_oldpwd)[len_until_char(*new_oldpwd, '=')] != '=')
		new_oldpwd = NULL;
	if (update_cd_pwd_oldpwd(&envp_status->envp, new_pwd, new_oldpwd) == 1)
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

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

static char	change_directory(t_envp *envp_status, char *pathname)
{
	int		error;
	char	*savepoint_cwd;

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
		error = chdir(savepoint_cwd);
		free(savepoint_cwd);
		ft_perror("minishell: cd: malloc: failed memory allocation\n");
		if (error != 0)
			perror(strerror(errno));
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
	if (ft_strncmp(argv[1], "-", -1) == 0
		&& (write(1, pathname, ft_strlen(pathname)) == -1
			|| write(1, "\n", 1) == -1))
	{
		free(pathname);
		return (1);
	}
	return (change_directory(envp_status, pathname));
}
