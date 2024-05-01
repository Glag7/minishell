/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:07:28 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/01 14:11:19 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_pwd_oldpwd(char **new_envp, size_t len, char *pwd,
		char *oldpwd)
{
	if (replace_var(new_envp, pwd, "PWD") == 1)
	{
		len--;
		new_envp[len] = pwd;
	}
	if (replace_var(new_envp, oldpwd, "OLDPWD") == 1)
	{
		len--;
		new_envp[len] = oldpwd;
	}
}

static bool	copy_cd_envp(char **new_envp, char **old_envp, char *new_pwd,
		char *new_oldpwd)
{
	size_t	i;
	char	*pwd;
	char	*oldpwd;

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
	i = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	i += (get_var(old_envp, "PWD") == NULL)
		+ (get_var(old_envp, "OLDPWD") == NULL);
	insert_pwd_oldpwd(new_envp, i, pwd, oldpwd);
	return (0);
}

static char	**alloc_new_envp(char **old_envp, size_t *new_len_ptr,
		size_t *old_len_ptr)
{
	char	**new_envp;
	size_t	new_len;
	size_t	old_len;

	old_len = 0;
	while (old_envp[old_len] != NULL)
		old_len++;
	new_len = old_len + (get_var(old_envp, "PWD") == NULL)
		+ (get_var(old_envp, "OLDPWD") == NULL);
	*new_len_ptr = new_len;
	*old_len_ptr = old_len;
	new_envp = malloc((new_len + 1) * sizeof(char *));
	return (new_envp);
}

static bool	update_cd_pwd_oldpwd(char ***envp, char *new_pwd,
		char **new_oldpwd_ptr)
{
	char	**new_envp;
	char	*new_oldpwd;
	char	**old_envp;
	size_t	old_len;
	size_t	new_len;

	old_envp = *envp;
	new_envp = alloc_new_envp(old_envp, &new_len, &old_len);
	if (new_envp == NULL)
		return (1);
	while (old_len <= new_len)
		new_envp[old_len++] = NULL;
	new_oldpwd = NULL;
	if (new_oldpwd_ptr != NULL)
		new_oldpwd = &(*new_oldpwd_ptr)
		[len_until_char(*new_oldpwd_ptr, '=') + 1];
	if (copy_cd_envp(new_envp, old_envp, new_pwd, new_oldpwd) == 1)
	{
		free(new_envp);
		return (1);
	}
	free(old_envp);
	*envp = new_envp;
	return (0);
}

bool	update_cd_envp(t_envp *envp_status)
{
	char	*new_pwd;
	char	**new_oldpwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
		return (1);
	new_oldpwd = get_var(envp_status->envp, "PWD");
	if (new_oldpwd != NULL
		&& (*new_oldpwd)[len_until_char(*new_oldpwd, '=')] != '=')
		new_oldpwd = NULL;
	if (update_cd_pwd_oldpwd(&envp_status->envp, new_pwd, new_oldpwd) == 1)
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}
