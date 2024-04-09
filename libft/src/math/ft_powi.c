/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:30:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 15:41:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int64_t	ft_powi(int64_t x, unsigned int n)
{
	unsigned int	i;
	int64_t			x_og;

	if (n == 0)
		return (1);
	i = 1;
	x_og = x;
	while (i * 2 < n)
	{
		x *= x;
		i *= 2;
	}
	while (i < n)
	{
		x *= x_og;
		i++;
	}
	return (x);
}
