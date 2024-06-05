/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maybe_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/05 15:22:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	maybe_del(t_list **tmp, t_list **curr, t_tok *tok, ssize_t size)
{
	if (size <= 0)
	{
		*tmp = (*curr)->next;
		ft_lstdelone(*curr, &free);
		*curr = *tmp;
		return ;
	}
	*tmp = *curr;
	tok->quote.str.s += tok->quote.str.len - size;
	tok->quote.str.len = size;
}
