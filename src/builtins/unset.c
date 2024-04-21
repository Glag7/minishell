/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:00:29 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/21 18:59:28 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(int argc, char **argv, char ***envp)
{
	int	i;
	char	*arg;

	if (argc <= 1)
		return (0);
	i = 1;
	arg = argv[1];
	while (arg != NULL)
	{
		if (remove_var(envp, arg) == 1)
			return (2);
		i++;
		arg = argv[i];
	}
	return (0);
}
