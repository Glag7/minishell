/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:13:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/24 14:02:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_lim(t_list *tmp, size_t i, t_hdoc *hdoc)
{
	return (0);
}

static int	add_prev(t_list **curr, t_list **tmp, t_tok **tok)
{
	*tok = malloc(sizeof(**tok));
	*tmp = ft_lstnew(tok);
	if (*tok == NULL || *tmp == NULL)
	{
		free(*tok);
		free(*tmp);
		return (ERR_AINTNOWAY);
	}
	ft_lstinsert(curr, *tmp, 0);
	return (0);
}

static int	search_hdoc(t_list *curr, t_list *tmp, t_tok *tok)
{
	size_t	i;
	t_hdoc	hdoc;
	int		err;

	i = -1;
	while (++i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '<' && tok->quote.str.s[i + 1] == '<')
		{
			err = search_lim(tmp, i, &hdoc);
			if (err)
				return (err);
			tok->quote.str.len = i;
			if (i != 0 && add_prev(&curr, &tmp, &tok))
				return (ERR_AINTNOWAY);
			*tok = (t_tok){.tok = HDOC, .hdoc = hdoc};
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
				else
					ft_perror(MSG_HDOC);
				*exc = 2;
				ft_lstclear(lst, &free_lbuild);
			}
			return ;
		}
		tmp = tmp->next;
	}
}
