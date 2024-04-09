/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:38:14 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/19 18:10:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlst **dlst, t_dlst *new)
{
	t_dlst	*tmp;
	t_dlst	*tmp2;

	tmp = *dlst;
	*dlst = new;
	if (tmp == NULL)
		return ;
	new->prev->next = tmp;
	tmp->prev->next = new;
	tmp2 = new->prev;
	new->prev = tmp->prev;
	tmp->prev = tmp2;
}
