/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:05:45 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/18 18:52:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list **lst, t_list *node, size_t n)
{
	size_t	i;
	t_list	*tmp;
	t_list	*next;

	i = 0;
	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = node;
		return ;
	}
	next = tmp->next;
	while (next && i < n)
	{
		tmp = next;
		next = tmp->next;
		i++;
	}
	tmp->next = node;
	ft_lstlast(node)->next = next;
}
