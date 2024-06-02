/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:22:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/02 17:09:02 by glaguyon         ###   ########.fr       */
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
		tok = (t_tok *)lst->content;
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

	len = count_words(lst);
	strs = malloc((len + 1) * sizeof(*strs));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (lst)
	{
		tok = (t_tok *)lst->content;
		if (tok->tok == TXT)
			strs[i++] = tok->s.s;
		else if (tok->tok == REDIR || tok->tok == HDOC)
			break ;
		lst = lst->next;
	}
	strs[i] = NULL;
	return (strs);
}

int	get_cmd(t_mini *mini, t_cmd *cmd, t_list *toparse)
{
	t_list	*redir;
	t_tok	*tk;

	redir = cmd->redir;
	while (redir)
	{
		tk = (t_tok *)redir->content;
		if (tk->tok == HDOC && tk->hdoc.expand && hdoc_replace(mini, tk->hdoc))
		{
			ft_lstclear(&cmd->redir, &free_lexec);
			ft_lstclear(&toparse, &free_lexec);
			return (1);
		}
		redir = redir->next;
	}
	cmd->cmd = lst_to_strs(toparse);
	if (cmd->cmd == NULL)
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		ft_lstclear(&cmd->redir, &free_lexec);
		ft_lstclear(&toparse, &free_lexec);
		return (1);
	}
	return (build_redirs(mini, cmd, toparse));
}
