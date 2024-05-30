/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/28 19:09:36 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static bool	get_option_nl(char **argv, size_t *i_ptr)
{
	bool	nl;
	char	*option;
	size_t	i;
	size_t	i_option;

	i = 1;
	nl = 1;
	option = argv[1];
	while (option != NULL && option[0] == '-' && option[1] == 'n')
	{
		nl = 0;
		i_option = 2;
		while (option[i_option] == 'n')
			i_option++;
		if (option[i_option] != '\0')
			break ;
		i++;
		option = argv[i];
	}
	*i_ptr = i;
	return (nl);
}

static int	write_loop(char **argv, bool nl, size_t i, int fd)
{
	char	*arg;

	arg = argv[i];
	while (arg != NULL)
	{
		if (g_sig == 2)
		{
			if (write(fd, "\n", 1) == -1)
				return (1);
			return (130);
		}
		if (write(fd, arg, ft_strlen(arg)) == -1
			|| (argv[i + 1] != NULL && write(fd, " ", 1) == -1))
			return (1);
		i++;
		arg = argv[i];
	}
	if (nl == 1 && write(fd, "\n", 1) == -1)
		return (1);
	return (0);
}

int	builtin_echo(int argc, char **argv, t_envp *envp_status, int *fds)
{
	size_t	i;

	(void)argc;
	(void)envp_status;
	return (write_loop(argv, get_option_nl(argv, &i), i, fds[WRITE]));
}
