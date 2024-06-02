/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:01:24 by glag              #+#    #+#             */
/*   Updated: 2024/06/02 16:32:26 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	stop_exec(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	if (argc <= 2)
		return (1);
	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		if (ft_is(DIGIT, argv[i][j]) == 0)
			return (1);
		while (argv[i][j] != '\0')
		{
			if (ft_is(DIGIT, argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	wrap_exit(t_mini *mini, int argc, char **argv)
{
	if (mini->forked == 0 && isatty(0))
		ft_perror("exit\n");
	mini->exc = builtin_exit(argc, argv, NULL, NULL);
	if (stop_exec(argc, argv) == 1)
		mini->err = ERR_SHUTUP;
}

void	wrap_builtin(t_mini *mini, char **argv, int *inout)
{
	size_t	argc;
	int		err;

	argc = 0;
	while (argv[argc])
		argc++;
	if (ft_strncmp(argv[0], "echo", -1) == 0)
		err = builtin_echo(argc, argv, &mini->envp, inout);
	else if (ft_strncmp(argv[0], "env", -1) == 0)
		err = builtin_env(argc, argv, &mini->envp, inout);
	else if (ft_strncmp(argv[0], "export", -1) == 0)
		err = builtin_export(argc, argv, &mini->envp, inout);
	else if (ft_strncmp(argv[0], "unset", -1) == 0)
		err = builtin_unset(argc, argv, &mini->envp, inout);
	else if (ft_strncmp(argv[0], "cd", -1) == 0)
		err = builtin_cd(argc, argv, &mini->envp, inout);
	else if (ft_strncmp(argv[0], "pwd", -1) == 0)
		err = builtin_pwd(argc, argv, &mini->envp, inout);
	else
		return (wrap_exit(mini, argc, argv));
	mini->exc = err;
	if (err == 2)
		mini->err = ERR_SHUTUP;
}
