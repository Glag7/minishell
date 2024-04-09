/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:12:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 18:40:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static void	print_addr(size_t n, int fd)
{
	char	toprint[18];
	int		i;

	toprint[16] = ':';
	toprint[17] = ' ';
	i = 16;
	while (i)
	{
		i--;
		toprint[i] = (n % 16 / 10) * 39 + 48 + n % 16;
		n /= 16;
	}
	write(fd, toprint, 18);
}

static void	print_line_hex(unsigned char *addr, int maxlen, int fd)
{
	char	toprint[40];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < maxlen)
	{
		toprint[j++] = (addr[i] / 16 / 10) * 39 + 48 + addr[i] / 16;
		toprint[j++] = (addr[i] % 16 / 10) * 39 + 48 + addr[i] % 16;
		if (i % 2)
			toprint[j++] = ' ';
		i++;
	}
	while (i < 16)
	{
		toprint[j++] = ' ';
		toprint[j++] = ' ';
		if (i % 2)
			toprint[j++] = ' ';
		i++;
	}
	write(fd, toprint, 40);
}

static void	print_line_hexl(unsigned char *addr, int maxlen, int fd)
{
	char	toprint[40];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 16 - maxlen)
	{
		toprint[j++] = ' ';
		toprint[j++] = ' ';
		if (i % 2)
			toprint[j++] = ' ';
		i++;
	}
	while (i < 16)
	{
		toprint[j++] = (addr[i] / 16 / 10) * 39 + 48 + addr[i] / 16;
		toprint[j++] = (addr[i] % 16 / 10) * 39 + 48 + addr[i] % 16;
		if (i % 2)
			toprint[j++] = ' ';
		i++;
	}
	write(fd, toprint, 40);
}

static void	print_line_char(char *addr, int max_len, bool rev, int fd)
{
	char	toprint[17];
	int		i;
	int		offset;

	offset = 0;
	while (rev && offset < 16 - max_len)
		toprint[offset++] = ' ';
	i = 0;
	while (i < max_len)
	{
		if (ft_is(PRINT, addr[i]))
			toprint[i + offset] = addr[i];
		else if (addr[i] == 0)
			toprint[i + offset] = '_';
		else
			toprint[i + offset] = '.';
		i++;
	}
	toprint[i + offset] = '\n';
	write(fd, toprint, i + offset + 1);
}

void	ft_printmem_fd(void *addr, int fd, size_t size)
{
	size_t	i;

	i = (16 - (size_t)addr % 16) % 16;
	if (i)
	{
		print_addr((size_t)addr, fd);
		print_line_hexl(addr, i, fd);
		print_line_char(addr, i, 1, fd);
	}
	while (i < size)
	{
		print_addr((size_t) addr + i, fd);
		if (size - i >= 16)
			print_line_hex(addr + i, 16, fd);
		else
			print_line_hex(addr + i, size - i, fd);
		if (size - i >= 16)
			print_line_char(addr + i, 16, 0, fd);
		else
			print_line_char(addr + i, size - i, 0, fd);
		i += 16;
	}
}
