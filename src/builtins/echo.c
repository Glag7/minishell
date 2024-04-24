/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/24 20:03:30 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(int argc, char **argv, char **envp)
{
	char	nl;
	size_t	i;

	(void)envp
	nl = 1;
	i = 1;
	if (argc > 1 && ft_strncmp(argv[1], "-n", -1) == 0)
	{
		nl = 0;
		i = 2;
	}
	while (argv[i] != NULL)
	{
		if (write(1, argv[i], ft_strlen(argv[i])) == -1)
			return (1);
		i++;
	}
	if (nl == 1 && write(1, "\n", 1) == -1)
		return (1);
	return (0);
}
