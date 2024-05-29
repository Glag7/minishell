/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:55 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/29 19:22:46 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static bool	print_env(char **envp, bool pwd, bool oldpwd, int fd)
{
	size_t	i;
	size_t	len;
	ssize_t	res;

	i = 0;
	while (envp[i] != NULL)
	{
		if (g_sig == 2)
			return (130);
		if (ft_in('=', envp[i]) != -1
			&& (ft_strncmp(envp[i], "PWD", 3) != 0 || pwd == 1)
			&& (ft_strncmp(envp[i], "OLDPWD", 6) != 0 || oldpwd == 1))
		{
			len = ft_strlen(envp[i]);
			envp[i][len] = '\n';
			res = write(fd, envp[i], len + 1);
			envp[i][len] = '\0';
			if (res < 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_env(int argc, char **argv, t_envp *envp_status, int *fds)
{
	if (argc > 1 && argv[1][0] == '-' &&
		((argv[1][1] != '\0' && argv[1][1] != '-')
			|| (argv[1][1] == '-' && argv[1][2] != '\0')))
	{
		ft_perror("minishell: env: invalid option '");
		ft_perror(argv[1]);
		ft_perror("'\n");
		return (125);
	}
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == '\0')
		return (0);
	if (argc > 1 && !(argv[1][0] == '-' && argv[1][1] == '-'))
	{
		ft_perror("minishell: env: too many arguments\n");
		return (1);
	}
	return (print_env(envp_status->envp, envp_status->show_pwd,
			envp_status->show_oldpwd, fds[WRITE]));
}
