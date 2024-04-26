/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:00:29 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/26 15:48:56 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(int argc, char **argv, t_envp *envp_status)
{
	size_t	i;
	char	*arg;

	if (argc <= 1)
		return (0);
	i = 1;
	arg = argv[1];
	while (arg != NULL)
	{
		remove_var(envp_status->envp, arg, free);
		if (ft_strncmp(arg, "PWD", -1) == 0)
			envp_status->show_pwd = 0;
		if (ft_strncmp(arg, "OLDPWD", -1) == 0)
			envp_status->show_oldpwd = 0;
		i++;
		arg = argv[i];
	}
	return (0);
}
