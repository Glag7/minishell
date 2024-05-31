/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:01:24 by glag              #+#    #+#             */
/*   Updated: 2024/05/31 13:06:59 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wrap_exit(t_mini *mini, int argc, char **argv)
{
	if (mini->forked == 0 && isatty(0))
		ft_perror("exit\n");
	if (argc == 2)
		mini->exc = builtin_exit(argc, argv, NULL, NULL);
	else
		mini->exc = builtin_exit(argc, argv, NULL, NULL);
	if (argc <= 2)
		mini->err = ERR_SHUTUP;
	else
		mini->exc = 1;
}

void	wrap_builtin(t_mini *mini, char **argv, int *inout)
{
	int	argc;
	int	err;

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
		mini->err = ERR_AINTNOWAY;
}
