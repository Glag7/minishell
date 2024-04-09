/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:10:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 14:52:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static inline void	ft_print_nbr(char *tmp, bool neg, int fd)
{
	int		i;
	char	c;
	char	toprint[21];

	i = 0;
	if (neg)
	{
		i++;
		toprint[0] = '-';
	}
	c = *(tmp - i);
	while (c)
	{
		toprint[i] = c;
		i++;
		c = *(tmp - i);
	}
	write(fd, toprint, i);
}

void	ft_putnbr_fd(int64_t n, int fd)
{
	uint64_t	num;
	char		tmp[21];
	int			numlen;
	bool		neg;

	neg = 0;
	num = n;
	if (n < 0)
	{
		neg = 1;
		num = -n;
	}
	*tmp = '\0';
	numlen = 1;
	while (num || numlen == 1)
	{
		tmp[numlen] = num % 10 + '0';
		num /= 10;
		numlen++;
	}
	ft_print_nbr(tmp + numlen + neg - 1, neg, fd);
}
