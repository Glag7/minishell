/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:31:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/24 14:31:23 by glaguyon         ###   ########.fr       */
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
		exec = exec->next;
	}
	return (lst);
}

static void	expand_vars(t_list *toparse, t_mini *mini, int *has_wdcard)
{
	t_tok	*tok;

	*has_wdcard = 0;
	while (toparse)
	{
		tok = (t_tok *)toparse->content;
		if (tok->tok == VAR)
			tok->var.str = varchr(tok->var.str, mini->envp.envp, mini);
		else if (tok->tok == WDCARD)
			*has_wdcard = 1;
		toparse = toparse->next;
	}
}

static void	replace_var_quote(t_list *toparse)
{
	t_tok	*tok;

	while (toparse)
	{
		tok = (t_tok *)toparse->content;
		if (tok->tok == VAR)
			tok->tok = UNDEF;
		toparse = toparse->next;
	}
}

static int	parse_cmd_txt(t_mini *mini,
	t_list *toparse, t_cmd *cmd, int has_wdcard)
{
	t_str	*fnames;

	fnames = NULL;
	if (has_wdcard && (get_fnames(mini, &fnames)
			|| exp_wdcard(mini, toparse, fnames)
			|| exp_wdcard(mini, cmd->redir, fnames)))
	{
		ft_lstclear(&cmd->redir, &free_lexec);
		ft_lstclear(&toparse, &free_lexec);
		free_fnames(fnames);
		return (1);
	}
	//free fnames ici si erreur
	
	/*garder le tok au debut puis transormer en t_redir au word_splitting	
	// *: remplacer par une liste chainee de txt
	//	non caca pour free, il faut juste traiter le wdcard comme ca
	//word splitting
	//
	//exec if pipe before && pipe after etc
	//parsing, fork ou pas
	//redir
	//exec
	*/
	ft_lstclear(&toparse, &free_lexec);//rm or use free
	free_fnames(fnames);
	return (0);
}

int	parse_cmd(t_mini *mini, t_list *exec, t_cmd *cmd)
{
	t_list				*toparse;
	int					has_wdcard;
	static const t_tok	space = {UNDEF, .quote = {0, .str = {" ", 1}}};

	toparse = dup_exec(exec, mini);
	if (toparse == NULL)
		return (1);
	expand_vars(toparse, mini, &has_wdcard);
	if (get_redir(mini, toparse, space, cmd))
	{
		ft_lstclear(&toparse, &free);
		return (1);
	}
	replace_var_quote(toparse);
	replace_var_quote(cmd->redir);
	if (split_words(mini, &toparse) || split_words(mini, &cmd->redir))
	{
		ft_lstclear(&cmd->redir, &free_lexec);
		ft_lstclear(&toparse, &free_lexec);
		return (1);
	}
	return (parse_cmd_txt(mini, toparse, cmd, has_wdcard));
}
