/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:13:15 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/20 19:30:03 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEMPORARY FILE

int	builtin_unset(int argc, char **argv, char ***envp)// doit modifier envp -> triple pointeur
{
	int	i;
	char	*var;

	i = 1;
	while (i < argc)
	{
		var = ft_strjoin(argv[i], "=");
		if (var == NULL)
		{
			ft_perror("minishell: unset: malloc: failed memory allocation\n");
			return (2);
		}
		if (remove_var(envp, var))
		{
			free(var);
			return (2);
		}
		free(var);
		i++;
	}
	return (0);
}

int	builtin_export(int argc, char **argv, char ***envp)// doit modifier envp -> triple pointeur
// gerer export a+=a, gerer export (tri ordre ascii + declare -x)
{
	
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
