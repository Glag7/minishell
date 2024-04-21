/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:40:04 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/21 19:38:14 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	strgreater(char *str1, char *str2)// return 1 if str1 > str2, 0 otherwise
{
	size_t	i;
	char	c1;
	char	c2;

	if (str1 == NULL)
		return (0);
	if (str2 == NULL)
		return (1);
	i = 0;
	c1 = str1[0];
	c2 = str2[0];
	while (c1 != 0 && c2 != 0)
	{
		if (c1 < c2)
			return (0);
		i++;
		c1 = str1[i];
		c2 = str2[i];
	}
	if (c1 == c2)
		return (0);
	return (1);
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

int	remove_var(char ***envp, char *var)
{
	char	**new_envp;
	char	**old_envp;
	size_t	len;
	size_t	i_old;
	size_t	i_new;
	size_t	len_var;

	old_envp = *envp;
	len = 0;
	len_var = ft_strlen(var);
	i_old = 0;
	while (old_envp[i_old] != NULL)
	{
		if (ft_strncmp(old_envp[i_old], var, len_var) != 0
			|| old_envp[i_old][len_var] == '=' || old_envp[i_old][len_var] == '\0')
			len++;
		i_old++;
	}
	new_envp = malloc((len + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	new_envp[len] = NULL;
	i_old = 0;
	i_new = 0;
	while (i_old < len)
	{
		if (ft_strncmp(old_envp[i_old], var, len_var) != 0
			|| old_envp[i_old][len_var] == '=' || old_envp[i_old][len_var] == '\0')
			new_envp[i_new++] = old_envp[i_old];
		else
			free(old_envp[i_old]);
		i_old++;
	}
	free(old_envp);
	*envp = new_envp;
	return (0);
}
