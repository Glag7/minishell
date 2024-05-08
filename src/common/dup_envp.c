/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/03 19:57:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_shlvl(char **envp, size_t *len)
{
	char	**old_shlvl;
	char	*new_shlvl;

	old_shlvl = get_var(envp, "SHLVL");
	if (old_shlvl == NULL)
	{
		old_shlvl = &envp[*len];
		(*len)++;
	}
	if (*old_shlvl == NULL || ft_strlen(*old_shlvl) <= 6
		|| check_numeric(&(*old_shlvl)[6]) == 0)
		new_shlvl = ft_strdup("SHLVL=1");
	else if ((int)(ft_atoi(&(*old_shlvl)[6]) + 1) < 0)
		new_shlvl = ft_strdup("SHLVL=0");
	else
		new_shlvl = increment_shlvl(*old_shlvl);
	if (new_shlvl == NULL)
		return (1);
	free(*old_shlvl);
	*old_shlvl = new_shlvl;
	return (0);
}

static int	update_oldpwd(char **envp, size_t *len)
{
	char	**old_oldpwd;

	old_oldpwd = get_var(envp, "OLDPWD");
	if (old_oldpwd == NULL)
	{
		envp[*len] = ft_strdup("OLDPWD");
		if (envp[*len] == NULL)
			return (1);
		(*len)++;
		return (0);
	}
	if (ft_strlen(*old_oldpwd) > 6 && access(&(*old_oldpwd)[7], F_OK) == -1)
	{
		remove_var(envp, "OLDPWD", free);
		(*len)--;
	}
	return (0);
}

static int	update_pwd(char **envp, size_t *len)
{
	char	**old_pwd;
	char	*pwd;
	char	*new_pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	new_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (new_pwd == NULL)
		return (1);
	old_pwd = get_var(envp, "PWD");
	if (old_pwd != NULL)
	{
		free(*old_pwd);
		*old_pwd = new_pwd;
	}
	else
	{
		envp[*len] = new_pwd;
		(*len)++;
	}
	return (0);
}

static int	check_pwd_shlvl(char ***envp_ptr, size_t len)
{
	char	**envp;

	envp = *envp_ptr;
	envp[len + 1] = NULL;
	envp[len + 2] = NULL;
	envp[len + 3] = NULL;
	if (update_pwd(envp, &len) != 0)
	{
		ft_freearr(envp);
		*envp_ptr = NULL;
		return (ERR_AINTNOWAY);
	}
	if (update_oldpwd(envp, &len) != 0)
	{
		ft_freearr(envp);
		*envp_ptr = NULL;
		return (ERR_AINTNOWAY);
	}
	if (update_shlvl(envp, &len) != 0)
	{
		ft_freearr(envp);
		*envp_ptr = NULL;
		return (ERR_AINTNOWAY);
	}
	return (0);
}

int	dup_envp(char ***envp_ptr)
{
	char	**envp;
	size_t	len;
	size_t	i;

	envp = *envp_ptr;
	len = 0;
	while (envp[len] != NULL)
		len++;
	*envp_ptr = malloc((len + 4) * sizeof(char *));
	if (*envp_ptr == NULL)
		return (ERR_AINTNOWAY);
	(*envp_ptr)[len] = NULL;
	i = 0;
	while (i < len)
	{
		(*envp_ptr)[i] = ft_strdup(envp[i]);
		if ((*envp_ptr)[i] == NULL)
		{
			ft_freearr(*envp_ptr);
			*envp_ptr = NULL;
			return (ERR_AINTNOWAY);
		}
		i++;
	}
	return (check_pwd_shlvl(envp_ptr, len));
}
