/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/02 17:47:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(int *error)
{
	*error = 1;
	return (2);
}

static int	get_exit_code(char *arg, int *error)
{
	size_t	i;
	long	nbr;
	char	sign;

	i = 0;
	while (arg[i] == ' ')
		i++;
	sign = -1;
	if (arg[i] == '-')
		sign = 1;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (ft_is(DIGIT, arg[i]) == 0)
		return (exit_error(error));
	nbr = 0;
	while (arg[i] != '\0')
	{
		nbr = 10 * nbr - arg[i] + 48;
		if (ft_is(DIGIT, arg[i]) == 0 || nbr > 0 || (sign == -1 && (-nbr) < 0))
			return (exit_error(error));
		i++;
	}
	return ((sign * nbr) & 255);
}

int	builtin_exit(size_t argc, char **argv, t_envp *envp_status, int *exit_mini)
{
	int	exitcode;
	int	error;

	(void)envp_status;
	if (argc <= 1)
	{
		*exit_mini = ERR_SHUTUP;
		return (0);
	}
	error = 0;
	exitcode = get_exit_code(argv[1], &error);
	if (error == 1)
	{
		ft_perror3("minishell: exit: ", argv[1],
			": numeric argument required\n");
		*exit_mini = ERR_SHUTUP;
		return (2);
	}
	if (argc > 2)
	{
		ft_perror("minishell: exit: too many arguments\n");
		return (1);
	}
	*exit_mini = ERR_SHUTUP;
	return (exitcode);
}
