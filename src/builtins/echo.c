/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/01 13:58:05 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_echo(int argc, char **argv, char **envp)
{
	bool	nl;
	char	*arg;
	int		res;
	size_t	len;
	size_t	i;

	(void)envp;
	(void)argc;
	nl = get_option_nl(argv, &i);
	arg = argv[i];
	while (arg != NULL)
	{
		len = ft_strlen(arg);
		if (argv[i + 1] != NULL)
			arg[len] = ' ';
		res = write(1, arg, len + 1);
		arg[len] = '\0';
		if (res == -1)
			return (1);
		i++;
		arg = argv[i];
	}
	if (nl == 1 && write(1, "\n", 1) == -1)
		return (1);
	return (0);
}
