/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:03:09 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/23 16:01:31 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_op(t_list **lst, int *i, int j, int type)
{
	if (j)
		return (0);
}

static int	search_op(t_list **lst, t_list *curr, int *i)
{
	t_tok	*tok;
	size_t	j;

	j = 0;
	tok = (t_tok *)curr->content;
	while (j < tok->quote.str.len)
	{
		if (tok->quote.str.s[j] == '&' && tok->quote.str.s[j + 1] == '&')
			return (add_op(lst, &i, j, AND));
		else if (tok->quote.str.s[j] == '|' && tok->quote.str.s[j + 1] == '|')
			return (add_op(lst, &i, j, OR));
		else if (tok->quote.str.s[j] == '|')
			return (add_op(lst, &i, j, PIPE));
		j++;
	}
	return (0);
}

void	parse_op(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;
	size_t	i;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0
			&& search_op(lst, tmp, &i))
		{
			*err = ERR_AINTNOWAY;
			*exc = 2;
			ft_lstclear(lst, &free);
			return ;
		}
		i++;
		tmp = tmp->next;
	}
}
