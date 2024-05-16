/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:14:35 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/16 13:36:27 by glaguyon         ###   ########.fr       */
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
		if (tok->tok == VAR)
			tok->var.s = varchr(tok->var.s, mini->envp.envp);
		exec = exec->next;
	}
	return (lst);
}

static int	get_redir(t_mini *mini, t_list *toparse,
	const t_tok space, t_cmd *cmd)
{
	t_list	*curr;
	t_list	*tmp;
	t_tok	*tok;

	curr = toparse;
	while (curr)
	{
		if (((t_tok *)curr->content)->tok == REDIR)
		{
			tok = malloc(sizeof(*tok));
			tmp = ft_lstnew(tok);
			if (tok == NULL || tmp == NULL)
			{
				free(tok);
				free(tmp);
				mini->exc = 2;
				mini->err = ERR_AINTNOWAY;
				ft_lstclear(&toparse, &free);
				ft_lstclear(&cmd->redir, &free);
				return (1);
			}
			tok = *(t_tok *)curr->content;
			ft_lstadd_back(&cmd->redir, tmp);
			//epic steal
			*(t_tok *)curr->content = space;
		}
		curr = curr->next;
	}
	return (0);
}//garder le tok au debut puis transormer en t_redir au word_splitting

int	parse_cmd(t_mini *mini, t_list *exec, t_cmd *cmd)
{
	t_list		*toparse;
	t_list		*tmp;
	const t_tok	space = {UNDEF, .quote = {0, .str = {" ", 1}}};

	toparse = dup_exec(exec, mini);
	if (toparse == NULL)
		return (1);
	if (get_redir(mini, toparse, space, cmd))
		return (1);
	//exec if pipe before && pipe after etc
	//parsing, fork ou pas
	//signaux
	//redir
	//exec
	ft_lstclear(&toparse, &free);
	return (0);
}
//enlever les redir, remplacer par " "
//*: remplacer par une quote nv 0
//word splitting
//
//redir: if name[0] == NULL || name[1] != NULL : bomba
