/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:26:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/09 18:36:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_slice(t_list **quotes, t_quote **slice)
{
	t_list	*tmp;

	*slice = malloc(sizeof(*slice));
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

t_list	*parse_quotes(char *s, int *err)
{
	t_list	*quotes;
	t_quote	*slice;
	char	*tmp;

	quotes = NULL;
	while (*s)
	{
		*err = add_new_slice(&quotes, &slice);
		if (*err)
			return (NULL);
		slice->str.s = s;
		slice->str.len = 0;
		slice->qtype = 0;
		if (*s == '\'' || *s == '\"')
		{
			slice->str.s += 1;
			slice->qtype = 1 + (*s == '\"');
			tmp = ft_strchr(s + 1, *s);
			if (tmp == NULL)
			{
				*err = ERR_PARSE;
				return (quotes);
			}
			slice->str.len = tmp - s - 1;
			s = tmp + 1;
		}
		else while (*s && *s != '\'' && *s != '\"')
		{
			s++;
			slice->str.len += 1;
		}
	}
	return (quotes);
}
