/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:34:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/28 15:55:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*free_wdcard(t_list *lst)
{
	t_list	*ret;

	ret = NULL;
	while (lst && (((t_tok *)lst->content)->tok == WDCARD
			|| ((t_tok *)lst->content)->tok == TXT))
	{
		ret = lst->next;
		ft_lstdelone(lst, &free_lexec);
		lst = ret;
	}
	return (ret);
}

void	free_fnames(t_str *fnames)
{
	size_t	i;

	if (fnames == NULL)
		return ;
	i = 0;
	while (fnames[i].s)
	{
		free(fnames[i].s);
		i++;
	}
	free(fnames);
}

void	free_lbuild(void *tok_)
{
	t_tok	*tok;

	tok = tok_;
	if (tok->tok == HDOC)
		free(tok->hdoc.lim.s);
	else if (tok->tok == TXT)
		free(tok->s.s);
	else if (tok->tok == VAR)
		free(tok->var.str.s);
	free(tok);
}

void	free_lexec(void *tok_)
{
	t_tok	*tok;

	tok = tok_;
	if (tok->tok == TXT)
		free(tok->s.s);
	free(tok);
}

void	free_lredir(void *redir_)
{
	t_redir	*redir;

	redir = redir_;
	if (redir->filename && redir->redir != HDOC_REDIR)
		ft_freearr(redir->filename);
	else
		free(redir->filename);
	free(redir);
}
