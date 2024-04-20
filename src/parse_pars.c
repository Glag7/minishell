/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/20 17:33:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//variable niveau parentheses
//jamais en negatif sinon juste par fermee
//entre 2 par de signes differents toujours un truc qui est pas des espaces

static int	add_pars(t_list **src, t_list **dst, int *err, int *exc)
{
	t_str	s;
	size_t	i;
	int		plevel;

	s = ((t_quote *)(*src)->content)->str;
	plevel = 0;
	i = 0;
	while (i < s.len)
	{
		i++;
	}
	return (0);
}

static int	dup_txt(t_list **src, t_list **dst, int *err, int *exc)
{
	t_tok	*tok;
	t_list	*tmp;

	tok = malloc(sizeof(*tok));
	tmp = ft_lstnew(tok);
	if (tok == NULL || tmp == NULL)
	{
		free(tmp);
		free(tok);
		ft_lstclear(src, &free);
		ft_lstclear(dst, &free);
		*err = ERR_AINTNOWAY;
		*exc = 2;
		return (1);
	}
	tok->tok = UNDEF;
	tok->quote = *(t_quote *)((*src)->content);
	ft_lstadd_back(dst, tmp);
	ft_lstpop(src, &free, 1);
	return (0);
}

t_list	*parse_pars(t_list *lst, int *err, int *exc)
{
	t_list	*pars;
	int		plevel;

	pars = NULL;
	plevel = 0;
	while (lst)
	{
		if ((((t_quote *)lst->content)->qtype == QUOTE
				|| ((t_quote *)lst->content)->qtype == DQUOTE)
			&& dup_txt(&lst, &pars, err, exc))
			return (NULL);
		else if (lst && ((t_quote *)lst->content)->qtype == 0)
		{
			plevel += add_pars(&lst, &pars, err, exc);
			if (pars == NULL || plevel < 0)
				break ;
		}
	}
	if (plevel != 0)
	{
		ft_lstclear(&pars, &free);
		*exc = 2;
	}
	return (pars);
}
