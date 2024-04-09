/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:32:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/03 19:48:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	ft_bzero(void *restrict s, size_t n)
{
	size_t	ptr;

	ptr = (size_t) s;
	if (n >= OPSIZE)
	{
		while (ptr % OPSIZE)
		{
			*(uint8_t *)ptr = 0;
			ptr += 1;
			n -= 1;
		}
	}
	while (n >= OPSIZE)
	{
		*(uint64_t *)ptr = 0;
		ptr += OPSIZE;
		n -= OPSIZE;
	}
	while (n)
	{
		*(uint8_t *)ptr = 0;
		ptr += 1;
		n -= 1;
	}
}
