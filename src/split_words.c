/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:14:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//skip espaces
//si skipped ajouter undef vide
//ajouter mot

static int	add_space(t_mini *mini, t_list **words)
{
	t_list	*tmp;
	t_tok	*tok;

	tok = malloc(sizeof(*tok));
	tmp = ft_lstnew(tok);
	if (tok == NULL || tmp == NULL)
	{
		free(tok);
		free(tmp);
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		return (2);
	}
	ft_lstadd_back(words, tmp);
	tok->tok = UNDEF;
	return (0);
}

static int	skip_spaces(t_mini *mini, t_list **lst, t_list **words)
{
	t_list	*curr;
	t_tok	*tok;
	int		space;

	space = 0;
	curr = *lst;
	while (curr && ((t_tok *)curr->content)->tok == UNDEF
		&& ((t_tok *)curr->content)->quote.qtype == 0)
	{
		tok = ((t_tok *)curr->content);
		while (tok->quote.str.len--
			&& ft_in(tok->quote.str.s++[0], " \t\n") != -1)
			space = 1;
		tok->quote.str.len++;
		tok->quote.str.s--;
		if (tok->quote.str.len)
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (1);
	*lst = curr;
	if (space)
		return (add_space(mini, words));
	return (0);
}

int	split_words(t_mini *mini, t_list **lst)
{
	t_list	*words;
	t_list	*curr;
	int		res;

	curr = *lst;
	words = NULL;
	while (curr)
	{
		res = skip_spaces(mini, &curr, &words);
		if (res)
			break ;
	}
	ft_lstclear(lst, &free_lexec);
	if (res > 1)
		ft_lstclear(&words, &free_lexec);
	*lst = words;
	return (res > 1);
}
