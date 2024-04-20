/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:55 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/20 19:29:27 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(int argc, char **argv, char **envp)// pas print si declare mais pas initialise (ie a= est print mais pas a)
{
	size_t	i;
	ssize_t	res;
	size_t	len;

	argv = NULL;
	if (argc != 1)
	{
		ft_perror("minishell: env: too many arguments\n");
		return (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		len = ft_strlen(envp[i]);
		envp[i][len] = '\n';
		res = write(1, envp[i], len + 1);
		envp[i][len] = '\0';
		if (res < 0)
			return (2);
		i++;
	}
	return (0);
}
