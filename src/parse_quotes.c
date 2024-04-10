/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:26:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/10 14:28:00 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_slice(t_list **quotes, t_quote **slice)
{
	t_list	*tmp;

	*slice = malloc(sizeof(**slice));
	if (*slice == NULL)
	{
		ft_lstclear(quotes, &free);
		return (ERR_AINTNOWAY);
	}
	tmp = ft_lstnew(*slice);
	if (tmp == NULL)
	{
		free(*slice);
		ft_lstclear(quotes, &free);
		return (ERR_AINTNOWAY);
	}
	ft_lstadd_back(quotes, tmp);
	return (0);
}

static int	add_quoted(t_quote *slice, int *err, char *s, bool dollar)
{
	char	*tmp;

	slice->str.s += 1 + dollar;
	slice->qtype = 1 + (s[dollar] == '\"');
	tmp = ft_strchr(s + 1 + dollar, s[dollar]);
	if (tmp == NULL)
	{
		*err = ERR_PARSE;
		return (1);
	}
	slice->str.len = tmp - s - 1 - dollar;
	return (0);
}

t_list	*parse_quotes(char *s, int *err)
{
	t_list	*quotes;
	t_quote	*slice;

	quotes = NULL;
	while (*s)
	{
		*err = add_new_slice(&quotes, &slice);
		if (*err)
			return (NULL);
		*slice = (t_quote){0, (t_str){s, 0}};
		if (s[*s == '$'] == '\'' || s[*s == '$'] == '\"')
		{
			if (add_quoted(slice, err, s, *s == '$'))
				return (quotes);
			s += slice->str.len + 2 + (*s == '$');
			continue ;
		}
		while (*s && s[*s == '$'] != '\'' && s[*s == '$'] != '\"')
		{
			s++;
			slice->str.len += 1;
		}
	}
	return (quotes);
}
