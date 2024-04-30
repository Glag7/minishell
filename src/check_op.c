/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:00:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/30 17:17:26 by glaguyon         ###   ########.fr       */
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

static inline void	init_var(int *notempty, int *need_nompty)
{
	*need_nompty = 1;
	*notempty = 0;
}

int	check_op(t_list *lst)
{
	t_tok	*tok;
	int		notempty;
	int		need_nompty;
	int		op;

	init_var(&notempty, &need_nompty);
	op = 0;
	while (lst)
	{
		tok = ((t_tok *)lst->content);
		op |= (tok->tok == OP || tok->tok == PIPE);
		if ((tok->tok == OP || tok->tok == PIPE) && (need_nompty || !notempty))
			return (1);
		else if ((tok->tok == OP || tok->tok == PIPE))
		{
			notempty = 0;
			need_nompty = 1;
		}
		else if (tok->tok == PAR)
			notempty = tok->type == CLOSE;
		else if (tok->quote.qtype || is_notempty(tok->quote))
			found_txt(&notempty, &need_nompty);
		lst = lst->next;
	}
	return (need_nompty && op);
}
