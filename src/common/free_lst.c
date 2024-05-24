/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:34:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/24 13:22:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_lredir(void *tok_)//?
{
	t_tok	*tok;

	tok = tok_;//hdoc : char ** aussi pour faire simple
	if (tok->tok == REDIR)
		free(tok->var.str.s);//char **
	else if (tok->tok == VAR)
		free(tok->var.str.s);// ???
	free(tok);
}
