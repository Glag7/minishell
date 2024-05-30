/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:00:29 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/28 19:15:34 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

int	builtin_unset(int argc, char **argv, t_envp *envp_status, int *fds)
{
	size_t	i;
	char	*arg;

	(void)fds;
	if (argc <= 1)
		return (0);
	i = 1;
	arg = argv[1];
	while (arg != NULL)
	{
		if (g_sig == 2)
			return (130);
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
