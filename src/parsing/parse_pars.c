/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/02 19:58:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_remaining(t_list *curr, t_tok *tok, size_t i)
{
	t_list	*tmp;
	t_tok	*tmptok;
	size_t	j;

	j = i;
	while (j < tok->quote.str.len && ft_in(tok->quote.str.s[j], " \t\n") != -1)
		j++;
	if (j == tok->quote.str.len)
		return (0);
	tmptok = malloc(sizeof(*tmptok));
	tmp = ft_lstnew(tmptok);
	if (tmp == NULL || tmptok == NULL)
	{
		free(tmp);
		free(tmptok);
		return (1);
	}
	ft_lstinsert(&curr, tmp, 0);
	*tmptok = (t_tok){.tok = UNDEF, .quote = {0,
		.str = {tok->quote.str.s + i, tok->quote.str.len - i}}};
	return (0);
}

static int	add_par(t_list *curr, t_tok **tok, size_t i)
{
	t_list	*tmp;
	t_tok	*tmptok;

	tmptok = malloc(sizeof(*tmptok));
	tmp = ft_lstnew(tmptok);
	if (tmp == NULL || tmptok == NULL)
	{
		free(tmp);
		free(tmptok);
		return (1);
	}
	ft_lstinsert(&curr, tmp, 0);
	(*tok)->quote.str.len = i;
	*tok = tmptok;
	return (0);
}

static int	add_pars(t_list *curr, t_tok *tok)
{
	size_t	i;
	bool	notempty;

	i = 0;
	notempty = 0;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '(' || tok->quote.str.s[i] == ')')
		{
			if (add_remaining(curr, tok, i + 1))
				return (1);
			if (notempty && add_par(curr, &tok, i))
				return (1);
			*tok = (t_tok){.tok = PAR,
				.type = (((t_tok *)curr->content)->quote.str.s[i] == ')')};
			return (0);
		}
		notempty |= ft_in(tok->quote.str.s[i], " \t\n") == -1;
		i++;
	}
	return (0);
}

void	parse_pars(t_list **lst, int *err, int *exc)
{
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		if (((t_tok *)curr->content)->tok == UNDEF
			&& ((t_tok *)curr->content)->quote.qtype == 0
			&& add_pars(curr, (t_tok *)curr->content))
		{
			*err = ERR_AINTNOWAY;
			*exc = 2;
			ft_lstclear(lst, &free);
			return ;
		}
		curr = curr->next;
	}
	if (*lst && check_pars(*lst))
	{
		ft_perror(MSG_PAR);
		ft_lstclear(lst, &free);
		*exc = 2;
	}
}
