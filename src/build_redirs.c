/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/30 19:22:46 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_strs(t_list *lst);

static t_redir	*add_redir_lst(t_list **redirs, int type)
{
	t_list	*tmp;
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	tmp = ft_lstnew(redir);
	if (redir == NULL || tmp == NULL)
	{
		free(redir);
		free(tmp);
		return (NULL);
	}
	ft_lstadd_back(redirs, tmp);
	*redir = (t_redir){type, NULL};
	return (redir);
}

static int	build_hdoc(t_list **redirs, t_tok *tok)
{
	t_redir	*redir;
	char	**tmp;

	redir = add_redir_lst(redirs, HDOC_REDIR);
	if (redir == NULL)
		return (1);
	tmp = malloc(2 * sizeof(*tmp));
	if (tmp == NULL)
		return (1);
	tmp[1] = NULL;
	tmp[0] = tok->hdoc.lim.s;
	redir->filename = tmp;
	return (0);
}

static int	build_redir(t_list **redirs, t_list *curr)
{
	t_redir	*redir;

	redir = add_redir_lst(redirs, ((t_tok *)curr->content)->type);
	if (redir == NULL)
		return (1);
	redir->filename = lst_to_strs(curr->next);
	return (redir->filename == NULL);
}

void	free_lredir_nofree(void *redir_)
{
	t_redir	*redir;

	redir = redir_;
	free(redir->filename);
	free(redir);
}

int	build_redirs(t_mini *mini, t_cmd *cmd, t_list *toparse)
{
	t_list	*redirs;
	t_list	*lst;
	t_tok	*tok;

	ft_lstclear(&toparse, &free);
	redirs = NULL;
	lst = cmd->redir;
	while (lst)
	{
		tok = (t_tok *)lst->content;
		if ((tok->tok == REDIR && build_redir(&redirs, lst))
			|| (tok->tok == HDOC && build_hdoc(&redirs, tok)))
		{
			ft_lstclear(&redirs, &free_lredir_nofree);
			ft_lstclear(&cmd->redir, &free_lexec);
			mini->err = ERR_AINTNOWAY;
			mini->exc = 2;
			return (1);
		}
		lst = lst->next;
	}
	ft_lstclear(&cmd->redir, &free);
	cmd->redir = redirs;
	return (0);
}
