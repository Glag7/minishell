/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:03:09 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/23 17:07:21 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_op(t_list *curr, int i, int tokn, int type)
{
	t_list	*tmp;
	t_tok	*tok;

	if (((t_tok *)curr->content)->quote.str.len - i - 1 - (tokn == OP))
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tok == NULL || tmp == NULL)
		{
			free(tok);
			free(tmp);
			return (1);
		}
		*tok = (t_tok){.tok = UNDEF, .quote = (t_quote){0,
			(t_str){((t_tok *)curr->content)->quote.str.s + i + 1 + (tokn == OP),
				((t_tok *)curr->content)->quote.str.len - i - 1 - (tokn == OP)}}};
		ft_lstinsert(&curr, tmp, 0);
	}
	tok = ((t_tok *)curr->content);
	tok->quote.str.len = i;
	if (i != 0)
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tok == NULL || tmp == NULL)
		{
			free(tok);
			free(tmp);
			return (1);
		}
		ft_lstinsert(&curr, tmp, 0);
	}
	*tok = (t_tok){.tok = tokn, .type = type};
	return (0);
}

static int	search_op(t_list *curr)
{
	t_tok	*tok;
	size_t	i;

	i = 0;
	tok = (t_tok *)curr->content;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '&' && tok->quote.str.s[i + 1] == '&')
			return (add_op(curr, i, OP, AND));
		else if (tok->quote.str.s[i] == '|' && tok->quote.str.s[i + 1] == '|')
			return (add_op(curr, i, OP, OR));
		else if (tok->quote.str.s[i] == '|')
			return (add_op(curr, i, PIPE, 80085));
		i++;
	}
	return (0);
}

void	parse_op(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0
			&& search_op(tmp))
		{
			*err = ERR_AINTNOWAY;
			*exc = 2;
			ft_lstclear(lst, &free);
			return ;
		}
		tmp = tmp->next;
	}
	//check
}
