/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:11:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/01 18:19:47 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	ft_print(char *builtin, int fd, char *str, size_t len)
{
	ssize_t	error;

	error = write(fd, str, len);
	if (error == -1)
	{
		error = errno;
		ft_perror3("minishell: ", builtin, ": write(): ");
		ft_perror3(strerror(error), "\n", "");
		return (-1);
	}
	return (error);
}
