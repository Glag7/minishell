/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lbuild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:34:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/24 13:53:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_wdcard(void *tok_)
{
	t_tok	*tok;

	tok = tok_;
	if (tok->tok == VAR || tok->tok == TXT)
		free(tok->txt.s);
	free(tok);
}

void	free_lbuild(void *tok_)
{
	t_tok	*tok;

	tok = tok_;
	if (tok->tok == HDOC)
		free(tok->hdoc.lim.s);
	else if (tok->tok == VAR || tok->tok == TXT)
		free(tok->txt.s);
	else if (tok->tok == REDIR)
	{
		if (tok->tok == TXT || tok->tok == VAR)
			free(tok->redir.txt.s);
		else if (tok->tok == WDCARD)
			ft_lstclear(&tok->redir.wdcard, &free_wdcard);
	}
	else if (tok->tok == WDCARD)
		ft_lstclear(&tok->wdcard, &free_wdcard);
	free(tok);
}
