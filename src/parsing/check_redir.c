/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:54:28 by glag              #+#    #+#             */
/*   Updated: 2024/05/05 17:10:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	notempty(t_str str)
{
	size_t	i;

	i = 0;
	while (i < str.len)
	{
		if (ft_in(str.s[i], " \t\n") == -1)
			return (1);
		i++;
	}
	return (0);
}

int	check_redir(t_list *lst)
{
	t_tok	*tok;
	bool	need_txt;

	need_txt = 0;
	while (lst)
	{
		tok = (t_tok *)lst->content;
		if (tok->tok == REDIR)
		{
			if (need_txt)
				return (1);
			need_txt = 1;
		}
		else if (tok->tok == VAR || tok->tok == WDCARD
			|| (tok->tok == UNDEF && (tok->quote.qtype
					|| notempty(tok->quote.str))))
			need_txt = 0;
		else if ((tok->tok == UNDEF && tok->quote.qtype == 0
				&& !notempty(tok->quote.str)))
			;
		else if (need_txt)
			return (1);
		lst = lst->next;
	}
	return (need_txt);
}
