/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/04 13:49:04 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_spaces(char *arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_in(arg[i], " \t\n") != -1)
		i++;
	if (!arg[i])
		return (arg + i);
	j = i;
	while (arg[j])
		j++;
	j--;
	while (ft_in(arg[j], " \t\n") != -1)
		j--;
	arg[j + 1] = 0;
	return (arg + i);
}

static void	init_sign(char **arg, char *sign)
{
	*sign = -1;
	if (**arg == '-')
		*sign = 1;
	if (**arg == '-' || **arg == '+')
		(*arg)++;
}

static int	get_exit_code(char *arg, int *error)
{
	long	nbr;
	char	sign;

	arg = skip_spaces(arg);
	init_sign(&arg, &sign);
	if (ft_is(DIGIT, *arg) == 0)
	{
		*error = 1;
		return (2);
	}
	nbr = 0;
	while (*arg != '\0')
	{
		nbr = 10 * nbr - *arg + '0';
		if (ft_is(DIGIT, *arg) == 0 || nbr > 0 || (sign == -1 && (-nbr) < 0))
		{
			*error = 1;
			return (2);
		}
		arg++;
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
