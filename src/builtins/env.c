/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:55 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/04 15:05:26 by glaguyon         ###   ########.fr       */
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
		if (g_sig == SIGINT)
			return (130);
		if (ft_in('=', envp[i]) != -1
			&& (ft_strncmp(envp[i], "PWD=", 4) != 0 || pwd == 1)
			&& (ft_strncmp(envp[i], "OLDPWD=", 7) != 0 || oldpwd == 1))
		{
			len = ft_strlen(envp[i]);
			envp[i][len] = '\n';
			res = ft_print("env", fd, envp[i], len + 1);
			envp[i][len] = '\0';
			if (res < 0)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	env_error(char *arg)
{
	const char	i = 'i';

	if (arg[0] == '-' && arg[1] == 0)
	{
		ft_perror("env: invalid option -- '");
		write(STDERR_FILENO, &i, 1);
		ft_perror("'\n");
	}
	if (arg[0] == '-' && arg[1] != '-')
	{
		ft_perror("env: invalid option -- '");
		write(STDERR_FILENO, &arg[1], 1);
		ft_perror("'\n");
	}
	else
		ft_perror3("env: unrecognized option '", arg, "'\n");
	return (125);
}

int	builtin_env(size_t argc, char **argv, t_envp *envp_status, int *fds)
{
	if (argc > 1 && argv[1][0] == '-' && ft_strncmp(argv[1], "--", -1) != 0)
		return (env_error(argv[1]));
	if ((argc > 1 && ft_strncmp(argv[1], "--", -1) != 0) || argc > 2)
	{
		ft_perror("minishell: env: too many arguments\n");
		return (1);
	}
	return (print_env(envp_status->envp, envp_status->show_pwd,
			envp_status->show_oldpwd, fds[WRITE]));
}
