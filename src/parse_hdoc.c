/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:13:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/23 20:11:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_hdoc(t_list *curr, t_list *tmp, t_tok *tok)
{
	size_t	i;
	bool	expand;
	t_str	lim;

	i = -1;
	while (++i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '<' && tok->quote.str.s[i + 1] == '<')
		{
			//err = search_lim(tmp, i, &expand, &lim);//renvoyer erreur maloc ou parsing
			tok->quote.str.len = i;
			if (i != 0)
			{
				tok = malloc(sizeof(*tok));
				tmp = ft_lstnew(tok);
				if (tok == NULL || tmp == NULL)
				{
					free(tok);
					free(tmp);
					return (ERR_AINTNOWAY);
				}
				ft_lstinsert(&curr, tmp, 0);
			}
			*tok = (t_tok){.tok = HDOC, .hdoc = (t_hdoc){expand, lim}};
		}
	}
	return (0);
}

void	parse_hdoc(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;
	int		res;

	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0)
		{
			res = search_hdoc(tmp, tmp, ((t_tok *)tmp->content));
			if (res)
			{
				if (res == ERR_AINTNOWAY)
					*err = ERR_AINTNOWAY;
				*exc = 2;
				ft_lstclear(lst, &free_lbuild);
			}
			return ;
		}
		tmp = tmp->next;
	}
}
