/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <glaguyon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:10:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/19 18:20:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlst **dlst, void (*del)(void *))
{
	t_dlst	*start;
	t_dlst	*node;
	t_dlst	*next;

	node = *dlst;
	if (node == NULL)
		return ;
	start = node->prev;
	while (node != start)
	{
		next = node->next;
		if (del)
			del(node->content);
		free(node);
		node = next;
	}
	if (del)
		del(node->content);
	free(node);
	*dlst = NULL;
}
