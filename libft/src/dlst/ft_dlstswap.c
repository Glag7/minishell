/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:34:26 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/23 16:57:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstswap(t_dlst **dlst_addr)
{
	t_dlst	*dlst;
	t_dlst	*oldprev;
	t_dlst	*oldnext;

	dlst = *dlst_addr;
	*dlst_addr = dlst->next;
	if (dlst->next == dlst || dlst->next == dlst->prev)
		return ;
	oldnext = dlst->next;
	oldprev = dlst->prev;
	oldprev->next = oldnext;
	oldnext->next->prev = dlst;
	dlst->prev = dlst->next;
	dlst->next = oldnext->next;
	oldnext->prev = oldprev;
	oldnext->next = dlst;
}
