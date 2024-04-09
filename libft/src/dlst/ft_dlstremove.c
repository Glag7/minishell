/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <glaguyon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:17:26 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/28 16:11:16 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlst	*ft_dlstremove(t_dlst **dlst, ssize_t n)
{
	ssize_t	i;
	t_dlst	*tmp;

	i = 0;
	tmp = *dlst;
	if (n == 0)
		*dlst = tmp->next;
	while (n >= 0 && i < n)
	{
		tmp = tmp->next;
		i++;
	}
	while (n < 0 && i > n)
	{
		tmp = tmp->prev;
		i--;
	}
	if (tmp->next == tmp)
		*dlst = NULL;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	tmp->next = tmp;
	tmp->prev = tmp;
	return (tmp);
}
