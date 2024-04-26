/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wdcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:25:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/26 18:07:48 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: stop on <>

static int	fill_wdcard(t_list *wdcard, t_list **next)
{
	//si var ajouter var
	//si texte quote ajouter texte
	//si * ajouter *
	//si '<> \t\n' fini
	//si texte non quote juste l'ajouter
}

static int	start_wdcard(t_list **last_split, t_tok *tok)
{
	t_list	*tmp;
	t_list	*next;
	t_tok	*tmptok;
	int		err;

	tmptok = malloc(sizeof(*tmptok));
	tmp = ft_lstnew(tmptok);
	if (tmptok == NULL || tmp == NULL)
	{
		free(tmptok);
		free(tmp);
		return (1);
	}
	ft_lstinsert(last_split, tmp, 0);
	*tmptok = *tok;
	*tok = (t_tok){.tok = WDCARD, .wdcard = tmp};
	err = fill_wdcard(*last_split, &next);
	if (err)
		return (1);
	(*last_split)->next = next;
	*last_split = next
	return (0);
}

static int	add_wdcard(t_list **last_split,
		t_tok *tok, size_t offset)
{
	t_list	*tmp;
	t_tok	*tmptok;

	if (offset)
	{
		tmptok = malloc(sizeof(*tmptok));
		tmp = ft_lstnew(tmptok);
		if (tmptok == NULL || tmp == NULL)
		{
			free(tmptok);
			free(tmp);
			return (1);
		}
		ft_lstinsert(last_split, tmp, 0);
		*tmptok = (t_tok){.tok = UNDEF, .quote = {tok->quote.qtype,
			.str = {tok->quote.str.s + offset, tok->quote.str.len - offset}}};
		tok->quote.str.len = offset;
		*last_split = (*last_split)->next;
		tok = (t_tok *)(*last_split)->content;
	}
	return (start_wdcard(last_split, tok));
}

static int	search_wdcard(t_list *lst, t_list **last_split, t_tok *tok)
{
	size_t	i;
	size_t	lastspace;
	t_tok	*tmptok;

	i = -1;
	while (++i < tok->quote.str.len)
	{
		if (ft_in(tok->quote.str.s[i], " \t\n<>") != -1)
			*last_split = lst;
		if (i == tok->quote.str.len)
			*last_split = (*last_split)->next;
		if (tok->quote.str.s[i] == '*')
		{
			i = -1;
			lastspace = 0;
			tmptok = ((t_tok *)(*last_split)->content);
			while (tok->tok == UNDEF && tok->quote.qtype == 0
				&& ++i < tmptok->quote.str.len
				&& tmptok->quote.str.s[i] != '*')
				if (ft_in(tmptok->quote.str.s[i], " \t\n<>") != -1)
					lastspace = i + 1;
			return (add_wdcard(last_split, tmptok, lastspace));
		}
	}
	return (0);
}

void	parse_wdcard(t_list **lst, int *err, int *exc)
{
	t_list	*curr;
	t_list	*last_split;
	t_tok	*tok;

	curr = *lst;
	last_split = curr;
	while (curr)
	{
		tok = ((t_tok *)curr->content);
		if (tok->tok != UNDEF && tok->tok != VAR)
			last_split = curr->next;
		else if (tok->tok == UNDEF && tok->quote.qtype == 0
			&& search_wdcard(curr, &last_split, tok))
		{
			*exc = 2;
			*err = ERR_AINTNOWAY;
			ft_lstclear(lst, &free_lbuild);
			return ;
		}
		curr = curr->next;
	}
}
