/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/25 15:30:30 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(int argc, char **argv, char **envp)
{
	bool	nl;
	int		res;
	size_t	len;
	size_t	i;

	(void)envp;
	i = 1;
	nl = argc <= 1 || (argc > 1 && ft_strncmp(argv[1], "-n", -1) != 0);
	if (argc > 1 && ft_strncmp(argv[1], "-n", -1) == 0)
		i = 2;
	while (argv[i] != NULL)
	{
		len = ft_strlen(argv[i]);
		if (argv[i + 1] != NULL)
			argv[i][len] = ' ';
		res = write(1, argv[i], len + 1);
		argv[i++][len] = '\0';
		if (res == -1)
			return (1);
	}
	if (nl == 1 && write(1, "\n", 1) == -1)
		return (1);
	return (0);
}
