/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:01 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 17:30:50 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char	*s)
{
	write(2, s, ft_strlen(s));
}

void	check_err(int err, int forked)
{
	if (err == ERR_BYEBYE && forked == 0)
		ft_perror("exit\n");
	else if (err == ERR_AINTNOWAY)
		ft_perror(MSG_MALLOC);
}
