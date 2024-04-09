/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:10:45 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 14:52:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static inline void	ft_print_nbr(char *tmp, bool neg, int fd)
{
	int		i;
	char	c;
	char	toprint[66];

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

void	ft_putnbrbase_fd(int64_t n, int fd, char *base)
{
	uint64_t	num;
	int			numlen;
	int			len;
	char		tmp[66];
	bool		neg;

	num = n;
	len = ft_strlen(base);
	if (n < 0)
	{
		neg = 1;
		num = -n;
	}
	else
		neg = 0;
	*tmp = '\0';
	numlen = 1;
	while (num || numlen == 1)
	{
		tmp[numlen] = base[num % len];
		num /= len;
		numlen++;
	}
	ft_print_nbr(tmp + numlen + neg - 1, neg, fd);
}
