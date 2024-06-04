/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:40:04 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/04 14:11:19 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_until_char(char *str, char c)
{
	size_t	i;
	char	c_str;

	i = 0;
	c_str = str[0];
	while (c_str != 0 && c_str != c)
	{
		i++;
		c_str = str[i];
	}
	return (i);
}

char	**get_var(char **envp, char *var)
{
	size_t	i;
	size_t	len;
	size_t	len_var;

	len_var = ft_strlen(var);
	i = 0;
	while (envp[i] != NULL)
	{
		len = len_until_char(envp[i], '=');
		if (len == len_var && ft_strncmp(envp[i], var, len) == 0)
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

int	replace_var(char **envp, char *new, char *name)
{
	char	**var;

	var = get_var(envp, name);
	if (var == NULL)
		return (1);
	free(*var);
	*var = new;
	return (0);
}

void	remove_var(char **envp, char *var, void (*del)(void *))
{
	char	**var_to_remove;
	size_t	i;
	size_t	len;

	var_to_remove = get_var(envp, var);
	if (var_to_remove == NULL)
		return ;
	len = 0;
	while (envp[len] != NULL)
		len++;
	i = 0;
	while (i < len && envp[i] != *var_to_remove)
		i++;
	if (del != NULL)
		del(envp[i]);
	while (i < len)
	{
		envp[i] = envp[i + 1];
		i++;
	}
}

ssize_t	ft_print(char *builtin, int fd, char *str, size_t len)
{
	ssize_t	error;

	error = write(fd, str, len);
	if (error == -1)
	{
		error = errno;
		ft_perror3("minishell: ", builtin, ": write(): ");
		ft_perror3(strerror(error), "\n", "");
		return (-1);
	}
	return (error);
}
