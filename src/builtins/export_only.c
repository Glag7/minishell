/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:39:36 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/01 18:22:14 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static int	strgreater(void *ptr1, void *ptr2)
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

static void	selection_sort(void **arr, size_t len, int (*cmp)(void *, void *))
{
	void	*swap;
	size_t	i;
	size_t	i_min;
	size_t	i_sorted;

	i_sorted = 0;
	while (i_sorted < len)
	{
		i = i_sorted;
		i_min = i_sorted;
		while (i < len)
		{
			if (cmp(arr[i_min], arr[i]) > 0)
				i_min = i;
			i++;
		}
		swap = arr[i_sorted];
		arr[i_sorted] = arr[i_min];
		arr[i_min] = swap;
		i_sorted++;
	}
}

static char	**sort_envp(char **envp, bool pwd, bool oldpwd)
{
	char	**sorted;
	size_t	len;
	size_t	i;

	len = 0;
	while (envp[len] != NULL)
		len++;
	sorted = malloc((len + 1) * sizeof(char *));
	if (sorted == NULL)
		return (NULL);
	sorted[len] = NULL;
	i = 0;
	while (i < len)
	{
		sorted[i] = envp[i];
		i++;
	}
	selection_sort((void **)sorted, len, strgreater);
	remove_var(sorted, "_", NULL);
	if (pwd == 0)
		remove_var(sorted, "PWD", NULL);
	if (oldpwd == 0)
		remove_var(sorted, "OLDPWD", NULL);
	return (sorted);
}

static int	print_export(char *var, int fd)
{
	size_t	i;

	i = len_until_char(var, '=');
	if (ft_print("export", fd, "declare -x ", 11) == -1
		|| ft_print("export", fd, var, i) == -1)
		return (1);
	if (var[i] == '=' && (ft_print("export", fd, "=\"", 2) == -1
			|| ft_print("export", fd, &var[i + 1], ft_strlen(&var[i + 1])) == -1
			|| ft_print("export", fd, "\"\n", 2) == -1))
		return (1);
	if (var[i] != '=' && ft_print("export", fd, "\n", 1) == -1)
		return (1);
	return (0);
}

int	export_only(t_envp envp_status, int fd)
{
	char	**sorted;
	size_t	i;

	i = 0;
	sorted = sort_envp(envp_status.envp, envp_status.show_pwd,
			envp_status.show_oldpwd);
	if (sorted == NULL)
		return (2);
	while (sorted[i] != NULL)
	{
		if (g_sig == SIGINT)
		{
			free(sorted);
			return (130);
		}
		if (print_export(sorted[i], fd) != 0)
		{
			free(sorted);
			return (1);
		}
		i++;
	}
	free(sorted);
	return (0);
}
