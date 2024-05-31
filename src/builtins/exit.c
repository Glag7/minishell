/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/31 11:57:23 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(char *arg)
{
	ft_perror3("minishell: exit: ", arg, ": numeric argument required\n");
	return (2);
}

static int	get_exit_code(char *arg)
{
	size_t	i;
	long	nbr;
	char	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (arg[0] == '-')
		sign = -1;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (ft_is(DIGIT, arg[i]) == 0)
		return (exit_error(arg));
	while (arg[i] != '\0')
	{
		nbr = 10 * nbr + arg[i] - 48;
		if (ft_is(DIGIT, arg[i]) == 0 || nbr < 0)
		{
			ft_perror3("minishell: exit: ", arg,
				": numeric argument required\n");
			return (2);
		}
		i++;
	}
	return ((sign * nbr) & 255);
}

int	builtin_exit(size_t argc, char **argv, t_envp *envp_status, int *fds)
{
	(void)envp_status;
	(void)fds;
	if (argc <= 1)
		return (0);
	if (argc > 2)
	{
		ft_perror("minishell: exit: too many arguments\n");
		return (1);
	}
	return (get_exit_code(argv[1]));
}
