/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:13:15 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/21 20:06:42 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_min(char **envp, char *old_min)// trouve celui directement plus grand trie par ordre ascii, return NULL si old_min est deja le max ou si envp est vide
{
	char	*new_min;
	char	*current;
	size_t	i;

	i = 0;
	current = envp[0];
	while (current != NULL && strgreater(current, old_min) == 1)//pb
	{
		i++;
		current = envp[i];
	}
	if (current == NULL)
		return (NULL);
	new_min = current;
	i = 0;
	current = envp[0];
	while (current != NULL)//boucle infinie
	{
		if (strgreater(old_min, current) && strgreater(current, new_min))
			new_min = current;
		i++;
		current = envp[i];
	}
	return (new_min);
}

static char	export_only(char **envp)
{
	char	*min;
	size_t	len;
	size_t tmp = 0;

	min = get_next_min(envp, NULL);
	while (min != NULL)
	{
		if (write(1, "declare -x ", 11) == -1)
			return (2);
		len = len_until_char(min, '=');
		if (write(1, min, len) == -1)
			return (2);
		if (min[len] == '=')
		{
			if (write(1, "=\"", 2) == -1)
				return (2);
			if (write(1, &min[len + 1], ft_strlen(&min[len + 1])) == -1)
				return (2);
			if (write(1, "\"\n", 2) == -1)
				return (2);
		}
		else if (write(1, "\n", 1) == -1)
			return (2);
		min = get_next_min(envp, min);
		tmp++;
		if (tmp == 100)
			exit(0);
	}
	return (0);
}

int	builtin_export(int argc, char **argv, char ***envp)// gerer export a+=a + overwriting
{
	if (argc <= 1)
		return (export_only(*envp));
	// suite
	return (0);
}





int	builtin_exit(int argc, char **argv, char **envp)
{
	
	return (0);
}

int	builtin_echo(int argc, char **argv, char **envp)
{
	
	return (0);
}
