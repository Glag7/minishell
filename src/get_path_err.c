/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:01:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/31 15:04:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path_err(t_mini *mini, int err, char *name)
{
	if (err == ENOENT)
	{
		ft_perror3("minishell: ", name, ": ");
		ft_perror3("command not found", "\n", "");
		mini->exc = 127;
	}
	else
	{
		ft_perror3("minishell: ", name, ": ");
		ft_perror3(strerror(err), "\n", "");
		mini->exc = 126;
	}
}
