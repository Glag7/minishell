/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:39:58 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/25 14:44:23 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_var(t_list *lst, t_tok *tok, int qtype)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '$')
		{
			if (tok->quote.str.s[i + 1] == '?')
				len++;
			while (++i < tok->quote.str.len
				&& (ft_is(ALNUM, tok->quote.str.s[i])
					|| tok->quote.str.s[i] == '_'))
				len++;
			if (len)
				return (add_var(lst, tok, qtype, len));
		i++;
	}
	return (0);
}

void	parse_var(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;
	t_tok	*tok;

	tmp = *lst;
	while (tmp)
	{
		tok = ((t_tok *)tmp->content);
		if (tok->tok == UNDEF && tok->quote.qtype != QUOTE)
		{
			if (search_var(tmp, tok, tok->quote.qtype))
			{
				*err = ERR_AINTNOWAY;
				*exc = 2;
				ft_lstclear(lst, &free_lbuild);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
