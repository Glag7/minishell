/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:23:43 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/04 17:04:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	concatenate_var(char **new_envp, char *arg)
{
	char	**old_var;
	char	*new_var;
	char	c;
	size_t	i;
	size_t	len;

	i = len_until_char(arg, '+');
	c = arg[i];
	arg[i] = '\0';
	old_var = get_var(new_envp, arg);
	arg[i] = c;
	len = ft_strlen(*old_var) + ((*old_var)[i] != '=') + ft_strlen(&arg[i + 2]);
	new_var = malloc((len + 1) * sizeof(char));
	if (new_var == NULL)
		return (1);
	new_var[len] = '\0';
	ft_memcpy(new_var, *old_var, ft_strlen(*old_var));
	if ((*old_var)[i] != '=')
		new_var[i] = '=';
	ft_memcpy(&new_var[ft_strlen(*old_var) + ((*old_var)[i] != '=')],
		&arg[len_until_char(arg, '=') + 1],
		ft_strlen(&arg[len_until_char(arg, '=') + 1]));
	free(*old_var);
	*old_var = new_var;
	return (0);
}

static int	overwrite_var(char **new_envp, char *arg)
{
	char	**old_var;
	char	*new_var;
	char	c;
	size_t	i;

	new_var = ft_strdup(arg);
	if (new_var == NULL)
		return (1);
	i = len_until_char(arg, '=');
	c = arg[i];
	arg[i] = '\0';
	old_var = get_var(new_envp, arg);
	arg[i] = c;
	free(*old_var);
	*old_var = new_var;
	return (0);
}

static int	create_var(char **new_envp, char *arg)
{
	size_t	i;
	char	*new_var;

	new_var = ft_strdup(arg);
	if (new_var == NULL)
		return (1);
	i = len_until_char(new_var, '=') - 1;
	if (new_var[i] == '+')
	{
		while (new_var[i] != 0)
		{
			new_var[i] = new_var[i + 1];
			i++;
		}
	}
	i = 0;
	while (new_envp[i] != NULL)
		i++;
	new_envp[i] = new_var;
	return (0);
}

static int	update_var(char **new_envp, char *arg, t_envp *envp_status)
{
	size_t	i;

	i = len_until_char(arg, '=');
	if (ft_strncmp("PWD", arg, 3) == 0
		&& (arg[3] == '\0' || arg[3] == '=' || arg[3] == '+'))
		envp_status->show_pwd = 1;
	else if (ft_strncmp("OLDPWD", arg, 6) == 0
		&& (arg[6] == '\0' || arg[6] == '=' || arg[6] == '+'))
		envp_status->show_oldpwd = 1;
	if (check_existence(arg, new_envp) == 0
		&& arg[i] == '=' && i && arg[i - 1] == '+')
		return (concatenate_var(new_envp, arg));
	else if (check_existence(arg, new_envp) == 0
		&& arg[i] == '=')
		return (overwrite_var(new_envp, arg));
	else if (check_existence(arg, new_envp) == 1)
		return (create_var(new_envp, arg));
	return (0);
}

int	update_envp(char **new_envp, char **argv, t_envp *envp_status,
		size_t len)
{
	size_t	i;
	char	*arg;

	if (copy_envp(new_envp, envp_status->envp, len) == 1)
		return (1);
	i = 0;
	arg = argv[0];
	while (arg != NULL)
	{
		if (check_syntax(arg) == 0
			&& update_var(new_envp, arg, envp_status) == 1)
			return (2);
		i++;
		arg = argv[i];
	}
	return (0);
}
