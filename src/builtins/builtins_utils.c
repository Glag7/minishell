/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:40:04 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/20 19:07:36 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strappend(char *src1, char *src2, char mode)
{
	char	*dst;
	size_t	len_src1;
	size_t	len_src2;

	len_src1 = ft_strlen(src1);
	len_src2 = ft_strlen(src2);
	dst = malloc((len_src1 + len_src2 + 1) * sizeof(char));
	if (dst == NULL)
	{
		if (mode)
			free(src1);
		return (NULL);
	}
	dst[len_src1 + len_src2] = '\0';
	ft_memcpy(dst, src1, len_src1);
	ft_memcpy(&dst[len_src1], src2, len_src2);
	if (mode)
		free(src1);
	return (dst);
}

char	**get_var(char **envp, char *var)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

int	replace_var(char **envp, char *new, char *old_name)
{
	char	**var;

	var = get_var(envp, old_name);
	if (var == NULL)
		return (-1);
	free(*var);
	*var = new;
	return (1);
}

int	remove_var(char ***envp, char *var)
{
	char	**new_envp;
	char	**old_envp;
	size_t	len;
	size_t	i;
	size_t	j;

	old_envp = *envp;
	len = 0;
	i = 0;
	while (old_envp[i] != NULL)
	{
		if (ft_strncmp(old_envp[i], var, ft_strlen(var)) != 0)
			len++;
		i++;
	}
	new_envp = malloc((len + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	new_envp[len] = NULL;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp(old_envp[j], var, ft_strlen(var)) != 0)
		{
			new_envp[i] = old_envp[j];
			i++;
		}
		else
			free(old_envp[j]);
		j++;
	}
	free(old_envp);
	*envp = new_envp;
	return (0);
}
