/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:02:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/22 17:11:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	clean_error(t_mini *mini, t_cmd *cmd,
	t_tok *tok, t_list *tmp)
{
	mini->exc = 2;
	mini->err = ERR_AINTNOWAY;
	ft_lstclear(&cmd->redir, &free);
	free(tok);
	free(tmp);
}

static int	split_lastword(t_list *start, t_list *curr, size_t i)
{
	t_list	*tmp;
	t_tok	*tok;

	tmp = start;
	if (((t_tok *)curr->content)->tok == UNDEF
		&& ((t_tok *)curr->content)->quote.qtype == 0)
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tmp == NULL || tok == NULL)
		{
			free(tmp);
			free(tok);
			start->next = curr->next;
			curr->next = NULL;
			return (1);
		}
		*tok = *(t_tok *)curr->content;
		tok->quote.str = (t_str){tok->quote.str.s + i, tok->quote.str.len - i};
		((t_tok *)curr->content)->quote.str.len = i;
	}
	start->next = tmp;
	tmp->next = curr->next;
	curr->next = NULL;
	return (0);
}

static int	add_filename(t_list *start, t_list *curr)
{
	t_tok	*tok;
	size_t	i;

	while (curr)
	{
		tok = ((t_tok *)curr->content);
		i = 0;
		if (tok->tok == UNDEF && tok->quote.qtype == 0)
		{
			while (i < tok->quote.str.len
				&& ft_in(tok->quote.str.s[i], " \t\n") == -1)
				i++;
			if (i < tok->quote.str.len)
				break ;
		}
		if (curr->next && (((t_tok *)curr->next->content)->tok == HDOC
				|| ((t_tok *)curr->next->content)->tok == REDIR))
			break ;
		curr = curr->next;
	}
	if (!curr)
		start->next = curr;
	if (curr && split_lastword(start, curr, i))
		return (1);
	return (0);
}

static int	get_filename(t_mini *mini, t_list *start, t_cmd *cmd)
{
	t_list	*curr;
	t_tok	*tok;

	curr = start->next;
	tok = ((t_tok *)curr->content);
	while (tok->tok == UNDEF && tok->quote.qtype == 0)
	{
		while (tok->quote.str.len
			&& ft_in(tok->quote.str.s++[0], " \t\n") != -1)
			tok->quote.str.len--;
		if (tok->quote.str.len)
			tok->quote.str.s--;
		if (tok->quote.str.len)
			break ;
		start = curr;
		curr = curr->next;
		tok = ((t_tok *)curr->content);
	}
	ft_lstadd_back(&cmd->redir, curr);
	if (add_filename(start, curr))
	{
		clean_error(mini, cmd, NULL, NULL);
		return (1);
	}
	return (0);
}

int	get_redir(t_mini *mini, t_list *toparse,
	const t_tok space, t_cmd *cmd)
{
	t_list	*curr;
	t_list	*tmp;
	t_tok	*tok;

	curr = toparse;
	while (curr)
	{
		if (((t_tok *)curr->content)->tok == REDIR
			|| ((t_tok *)curr->content)->tok == HDOC)
		{
			tok = malloc(sizeof(*tok));
			tmp = ft_lstnew(tok);
			if (tok == NULL || tmp == NULL)
				clean_error(mini, cmd, tok, tmp);
			if (tok == NULL || tmp == NULL)
				return (1);
			*tok = *(t_tok *)curr->content;
			ft_lstadd_back(&cmd->redir, tmp);
			if (tok->tok != HDOC && get_filename(mini, curr, cmd))
				return (1);
			*(t_tok *)curr->content = space;
		}
		curr = curr->next;
	}
	return (0);
}
