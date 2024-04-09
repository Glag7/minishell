/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:35:29 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/19 01:53:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlst	*ft_dlstnew(void *content)
{
	t_dlst	*new;

	new = malloc(sizeof(t_dlst));
	if (new == NULL)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->content = content;
	return (new);
}
