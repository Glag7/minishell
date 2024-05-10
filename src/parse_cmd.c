/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:14:35 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/10 18:08:48 by glaguyon         ###   ########.fr       */
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

//fichiers d'avant parses quand ambiguous
//creer les redirections a partir de la liste
//si ambiguous mettre une valeur speciale genre len a -1
int	parse_cmd(t_mini *mini, t_list *exec, t_cmd *cmd)
{
	t_list	*toparse;
	t_list	*tmp;

	toparse = dup_exec(exec, mini);
	if (toparse == NULL)
		return (1);
	if (ambiguous_var(mini))//mettre les ambi
	//enlever var et chaines vide
	//expand les wdcard dans les redirections, ambi si besoin
	//expand les wdcard 

	//exec if pipe before && pipe after etc
	//parsing, fork ou pas
	//signaux
	//redir
	//exec
	ft_lstclear(&toparse, &freelexec);
	return (0);
}
