/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:22:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/28 14:51:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(t_list *lst)
{
	size_t	len;
	t_tok	*tok;

	len = 0;
	while (lst)
	{
		tok = (t_tok *)lst;
		if (tok->tok == TXT)
			len++;
		else if (tok->tok == REDIR || tok->tok == HDOC)
			break ;
		lst = lst->next;
	}
	return (len);
}

char	**lst_to_strs(t_list *lst)
{
	size_t	i;
	size_t	len;
	char	**strs;
	t_tok	*tok;

	len = count_words;
	strs = malloc((len + 1) * sizeof(*strs));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (lst)
	{
		tok = (t_tok *)lst;
		if (tok->tok == TXT)
			strs[i++] = tok->s.s;
		else if (tok->tok == REDIR || tok->tok == HDOC)
			break ;
		lst = lst->next;
	}
	return (strs);
}

int	get_cmd(t_mini *mini, t_cmd *cmd, t_list *toparse)
{
	t_list	*redir;
	t_tok	*tok;

	redir = cmd->redir;
	while (redir)
	{
		tok = (t_tok *)redir;
		if (tok->tok == HDOC && hdoc_replace(mini, tok->hdoc))
		{
			ft_lstclear(&cmd->redir, &free_lexec);
			ft_lstclear(&toparse, &free_lexec);
			return (1);
		}
		redir = redir->next;
	}
	cmd->cmd = lst_to_strs(toparse);
	ft_lstclear(&toparse, &free_lexec);
	if (cmd->cmd == NULL)
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		ft_lstclear(&cmd->redir, &free_lexec);
		return (1);
	}
	return (build_redirs(mini, cmd));
}
