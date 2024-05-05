/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:36:16 by glag              #+#    #+#             */
/*   Updated: 2024/05/05 17:08:28 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	add_remaining(t_list *curr, t_tok *tok,
	size_t i, int type)
{
	t_list	*tmp;
	t_tok	*tmptok;

	if (tok->quote.str.len - i - 1 - (type == APP))
	{
		tmptok = malloc(sizeof(*tmptok));
		tmp = ft_lstnew(tmptok);
		if (tmptok == NULL || tmp == NULL)
		{
			free(tmptok);
			free(tmp);
			return (1);
		}
		*tmptok = (t_tok){.tok = UNDEF, .quote = (t_quote){0, (t_str){
			tok->quote.str.s + i + 1 + (type == APP),
			tok->quote.str.len - i - 1 - (type == APP)}}};
		ft_lstinsert(&curr, tmp, 0);
	}
	return (0);
}

static int	add_redir(t_list *curr, t_tok *tok, size_t i, int type)
{
	t_list	*tmp;

	if (add_remaining(curr, tok, i, type))
		return (1);
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
	*tok = (t_tok){.tok = REDIR, .redir = type};
	return (0);
}

static int	search_redir(t_list *curr)
{
	t_tok	*tok;
	size_t	i;

	i = 0;
	tok = (t_tok *)curr->content;
	while (i < tok->quote.str.len)
	{
		if (tok->quote.str.s[i] == '>' && tok->quote.str.s[i + 1] == '>')
			return (add_redir(curr, tok, i, APP));
		else if (tok->quote.str.s[i] == '>')
			return (add_redir(curr, tok, i, OUT));
		else if (tok->quote.str.s[i] == '<')
			return (add_redir(curr, tok, i, IN));
		i++;
	}
	return (0);
}

void	parse_redir(t_list **lst, int *err, int *exc)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (((t_tok *)tmp->content)->tok == UNDEF
			&& ((t_tok *)tmp->content)->quote.qtype == 0
			&& search_redir(tmp))
		{
			*err = ERR_AINTNOWAY;
			*exc = 2;
			ft_lstclear(lst, &free_lbuild);
			return ;
		}
		tmp = tmp->next;
	}
	if (*lst && check_redir(*lst))
	{
		ft_perror(MSG_REDIR);
		*exc = 2;
		ft_lstclear(lst, &free_lbuild);
	}
}
