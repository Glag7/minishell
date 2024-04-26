/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:55 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/26 15:33:43 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	print_env(char **envp, bool pwd, bool oldpwd)
{
	size_t	i;
	size_t	len;
	ssize_t	res;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_in('=', envp[i]) != -1
			&& (ft_strncmp(envp[i], "PWD", 3) != 0 || pwd == 1)
			&& (ft_strncmp(envp[i], "OLDPWD", 6) != 0 || oldpwd == 1))
		{
			len = ft_strlen(envp[i]);
			envp[i][len] = '\n';
			res = write(1, envp[i], len + 1);
			envp[i][len] = '\0';
			if (res < 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_env(int argc, char **argv, t_envp envp_status)
{
	(void)argv;
	if (argc != 1)
	{
		ft_perror("minishell: env: too many arguments\n");
		return (1);
	}
	return (print_env(envp_status.envp, envp_status.show_pwd,
			envp_status.show_oldpwd));
}
