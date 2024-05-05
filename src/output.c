/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:01 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 19:10:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror3(char	*s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
}

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
