/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:35:07 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/25 15:35:27 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_var(char *var)
{
	char	*new_var;
	size_t	i;

	new_var = ft_strdup(var);
	if (new_var == NULL)
		return (NULL);
	i = len_until_char(new_var, '=');
	if (new_var[i] != '=' || new_var[i - 1] != '+')
		return (new_var);
	i--;
	while (new_var[i] != '\0')
	{
		new_var[i] = new_var[i + 1];
		i++;
	}
	return (new_var);
}

static char	create_var(char *var, char ***envp)
{
	char	**new_envp;
	char	**old_envp;
	char	*new_var;
	size_t	len;

	old_envp = *envp;
	len = 0;
	while (old_envp[len] != NULL)
		len++;
	new_envp = malloc((len + 2) * sizeof(char *));
	new_var = dup_var(var);
	if (new_envp == NULL || new_var == NULL)
	{
		free(new_envp);
		free(new_var);
		return (2);
	}
	new_envp[len + 1] = NULL;
	new_envp[len] = new_var;
	while (len--)
		new_envp[len] = old_envp[len];
	free(old_envp);
	*envp = new_envp;
	return (0);
}

static char	overwrite_var(char *var, char **envp)
{
	char	**old_var;
	char	*new_var;
	char	c;
	size_t	i;

	i = len_until_char(var, '=');
	if (var[i] == '\0')
		return (0);
	new_var = ft_strdup(var);
	if (new_var == NULL)
		return (2);
	c = var[i];
	var[i] = '\0';
	old_var = get_var(envp, var);
	var[i] = c;
	free(*old_var);
	*old_var = new_var;
	return (0);
}

static char	concatenate_var(char *var, char **envp)
{
	char	**old_var;
	char	*new_var;
	char	c;
	size_t	i;

	i = len_until_char(var, '+');
	c = var[i];
	var[i] = '\0';
	old_var = get_var(envp, var);
	var[i] = c;
	i += 2;
	if ((*old_var)[len_until_char(*old_var, '=')] != '=')
	{
		new_var = ft_strjoin(*old_var, "=");
		if (new_var == NULL)
			return (2);
		new_var = ft_strappend(new_var, &var[i], 1);
	}
	else
		new_var = ft_strjoin(*old_var, &var[i]);
	if (new_var == NULL)
		return (2);
	free(*old_var);
	*old_var = new_var;
	return (0);
}

char	export_to_envp(char **argv, char ***envp)
{
	size_t	i;
	char	error;
	char	*arg;

	error = 0;
	i = 0;
	arg = argv[0];
	while (arg != NULL)
	{
		if (check_syntax(arg) == 0)
		{
			if (check_existence(arg, *envp) == 0)
				error |= create_var(arg, envp);
			else if (arg[len_until_char(arg, '=')] == '='
				&& arg[len_until_char(arg, '=') - 1] == '+')
				error |= concatenate_var(arg, *envp);
			else
				error |= overwrite_var(arg, *envp);
			if ((error & 2) != 0)
				return (2);
		}
		i++;
		arg = argv[i];
	}
	return (0);
}
