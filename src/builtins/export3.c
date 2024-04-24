/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:39:36 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/24 19:40:09 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	selection_sort(void **arr, size_t len, char (*cmp)(void *, void *))
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

static char	**sort_envp(char **envp)
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
	return (sorted);
}

static char	print_export(char *var)
{
	size_t	i;

	i = len_until_char(var, '=');
	if (write(1, "declare -x ", 11) == -1 || write(1, var, i) == -1)
		return (1);
	if (var[i] == '=' && (write(1, "=\"", 2) == -1
			|| write(1, &var[i + 1], ft_strlen(&var[i + 1])) == -1
			|| write(1, "\"\n", 2) == -1))
		return (1);
	if (var[i] != '=' && write(1, "\n", 1) == -1)
		return (1);
	return (0);
}

char	export_only(char **envp)
{
	char	**sorted;
	size_t	i;

	i = 0;
	sorted = sort_envp(envp);
	if (sorted == NULL)
		return (2);
	while (sorted[i] != NULL)
	{
		if (print_export(sorted[i]) != 0)
		{
			free(sorted);
			return (1);
		}
		i++;
	}
	free(sorted);
	return (0);
}
