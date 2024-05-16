/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:14:35 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/17 00:23:27 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*dup_exec(t_list *exec, t_mini *mini)
{
	t_list	*lst;
	t_list	*tmp;
	t_tok	*tok;

	lst = NULL;
	while (exec && ((t_tok *)exec->content)->tok != PIPE
		&& ((t_tok *)exec->content)->tok != OP
		&& ((t_tok *)exec->content)->tok != PAR)
	{
		tok = malloc(sizeof(*tok));
		tmp = ft_lstnew(tok);
		if (tok == NULL || tmp == NULL)
		{
			mini->err = ERR_AINTNOWAY;
			mini->exc = 2;
			free(tok);
			free(tmp);
			ft_lstclear(&lst, &free);
			return (NULL);
		}
		ft_lstadd_back(&lst, tmp);
		*tok = *(t_tok *)exec->content;
		if (tok->tok == VAR)//TODO make this another func
			tok->var.s = varchr(tok->var.s, mini->envp.envp);
		exec = exec->next;
	}
	return (lst);
}

int	parse_cmd(t_mini *mini, t_list *exec, t_cmd *cmd)
{
	t_list				*toparse;
	static const t_tok	space = {UNDEF, .quote = {0, .str = {" ", 1}}};

	toparse = dup_exec(exec, mini);
	if (toparse == NULL)
		return (1);
	if (get_redir(mini, toparse, space, cmd))
	{
		ft_lstclear(&toparse, &free);
		return (1);
	}
	//garder le tok au debut puis transormer en t_redir au word_splitting	
	//*: remplacer par une quote nv 0
	//	non caca pour free, il faut juste traiter le wdcard comme ca
	//word splitting
	//
	//exec if pipe before && pipe after etc
	//parsing, fork ou pas
	//signaux
	//redir
	//exec
	//
	ft_lstclear(&toparse, &free);
	return (0);
}
