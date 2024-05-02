/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:26:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/02 18:34:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_slice(t_list **quotes, t_tok **slice,
	int *err, int *exc)
{
	t_list	*tmp;

	*slice = malloc(sizeof(**slice));
	if (*slice == NULL)
	{
		*err = ERR_AINTNOWAY;
		*exc = 2;
		ft_lstclear(quotes, &free);
		return (ERR_AINTNOWAY);
	}
	tmp = ft_lstnew(*slice);
	if (tmp == NULL)
	{
		*err = ERR_AINTNOWAY;
		*exc = 2;
		free(*slice);
		ft_lstclear(quotes, &free);
		return (ERR_AINTNOWAY);
	}
	ft_lstadd_back(quotes, tmp);
	return (0);
}

static int	add_quoted(t_quote *slice, int *exc, char *s, t_list *lst)
{
	char	*tmp;

	slice->str.s += 1 + (*s == '$');
	slice->qtype = 1 + (s[*s == '$'] == '\"');
	tmp = ft_strchr(s + 1 + (*s == '$'), s[*s == '$']);
	if (tmp == NULL)
	{
		*exc = 2;
		ft_lstclear(&lst, &free);
		ft_perror(MSG_QUOTE);
		return (1);
	}
	slice->str.len = tmp - s - 1 - (*s == '$');
	return (0);
}

t_list	*parse_quotes(char *s, int *err, int *exc)
{
	t_list	*quotes;
	t_tok	*slice;

	quotes = NULL;
	while (*s)
	{
		if (add_new_slice(&quotes, &slice, err, exc))
			return (NULL);
		*slice = (t_tok){UNDEF, .quote = {0, (t_str){s, 0}}};
		if (s[*s == '$'] == '\'' || s[*s == '$'] == '\"')
		{
			if (add_quoted(&slice->quote, exc, s, quotes))
				return (NULL);
			s += slice->quote.str.len + 2 + (*s == '$');
			continue ;
		}
		while (*s && s[*s == '$'] != '\'' && s[*s == '$'] != '\"')
		{
			s++;
			slice->quote.str.len += 1;
		}
	}
	return (quotes);
}
