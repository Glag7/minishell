/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:07:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 14:51:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	ft_putendl_fd(char *s, int fd, size_t len)
{
	if (len == NOLEN)
		len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
