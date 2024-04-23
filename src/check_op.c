/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:00:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/23 19:03:38 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_notempty(t_quote quote)
{
	size_t	i;
	int		notempty;

	notempty = 0;
	i = -1;
	while (++i < quote.str.len && !notempty)
		notempty |= (ft_in(quote.str.s[i], " \t\n") == -1);
	return (notempty);
}

static inline void	found_txt(int *notempty, int *need_notempty)
{
	*notempty = 1;
	*need_notempty = 0;
}

int	check_op(t_list *lst)
{
	t_tok	*tok;
	int		notempty;
	int		need_notempty;

	need_notempty = 1;
	notempty = 0;
	while (lst)
	{
		tok = ((t_tok *)lst->content);
		if ((tok->tok == OP || tok->tok == PIPE))
		{
			if ((need_notempty || !notempty))
				return (1);
			notempty = 0;
			need_notempty = 1;
		}
		else if (tok->tok == PAR && tok->type == CLOSE)
			notempty = 1;
		else if (tok->tok == PAR)
			need_notempty = 0;
		else if (tok->quote.qtype || is_notempty(tok->quote))
			found_txt(&notempty, &need_notempty);
		lst = lst->next;
	}
	return (need_notempty);
}
