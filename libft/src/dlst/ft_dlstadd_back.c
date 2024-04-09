/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:23:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/19 18:29:25 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlst **dlst, t_dlst *new)
{
	t_dlst	*tmp;
	t_dlst	*tmp2;

	tmp = *dlst;
	if (tmp == NULL)
	{
		*dlst = new;
		return ;
	}
	new->prev->next = tmp;
	tmp->prev->next = new;
	tmp2 = new->prev;
	new->prev = tmp->prev;
	tmp->prev = tmp2;
}
