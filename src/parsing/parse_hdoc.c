/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:13:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 18:03:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_prev(t_list **curr, t_tok **tok)
{
	t_list	*tmp;

	*tok = malloc(sizeof(**tok));
	tmp = ft_lstnew(*tok);
	if (*tok == NULL || tmp == NULL)
	{
		free(*tok);
		free(tmp);
		return (ERR_AINTNOWAY);
	}
	ft_lstinsert(curr, tmp, 0);
	return (0);
}

static int	search_hdoc(t_list *curr, t_list *tmp, t_tok *tok)
{
	size_t	i;
	t_hdoc	hdoc;
	int		err;
	int		notempty;

	i = -1;
	notempty = 0;
	hdoc = (t_hdoc){.expand = 1, .lim = (t_str){NULL, 0}};
	while (++i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '<' && tok->quote.str.s[i + 1] == '<')
		{
			err = search_lim(tmp, tok, i + 2, &hdoc);
			tok->quote.str.len = i;
			if (err == 0 && (i != 0 && notempty))
				err = add_prev(&curr, &tok);
			if (err == 0)
				*tok = (t_tok){.tok = HDOC, .hdoc = hdoc};
			if (err == ERR_AINTNOWAY)
				free(hdoc.lim.s);
			return (err);
		}
		notempty |= ft_in(tok->quote.str.s[i], " \t\n") == -1;
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
				return ;
			}
		}
		tmp = tmp->next;
	}
}
