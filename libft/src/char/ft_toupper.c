/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/01 00:13:57 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

inline int	ft_toupper(int c)
{
	if (ft_is(LOWER, c))
		return (c & TOLOWER);
	return (c);
}
