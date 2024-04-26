/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:40:04 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/26 17:03:04 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	strgreater(void *ptr1, void *ptr2)
{
	size_t	i;
	char	*str1;
	char	*str2;
	char	c1;
	char	c2;

	str1 = (char *)ptr1;
	str2 = (char *)ptr2;
	i = 0;
	c1 = str1[0];
	c2 = str2[0];
	while (c1 != 0 && c1 != '=' && c1 == c2)
	{
		i++;
		c1 = str1[i];
		c2 = str2[i];
	}
	if (c1 == 0 || c1 == '=')
		return (0);
	if (c2 == 0 || c2 == '=' || c1 > c2)
		return (1);
	return (0);
}

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
		if (mode != 0)
			free(src1);
		return (NULL);
	}
	dst[len_src1 + len_src2] = '\0';
	ft_memcpy(dst, src1, len_src1);
	ft_memcpy(&dst[len_src1], src2, len_src2);
	if (mode != 0)
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
		if (ft_strncmp(envp[i], var, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
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
