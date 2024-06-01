/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:31:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/01 17:03:43 by glaguyon         ###   ########.fr       */
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
			|| (toparse && exp_wdcard(mini, &toparse, fnames))
			|| (cmd->redir && exp_wdcard(mini, &cmd->redir, fnames))))
	{
		ft_lstclear(&cmd->redir, &free_lexec);
		ft_lstclear(&toparse, &free_lexec);
		free_fnames(fnames);
		return (1);
	}
	free_fnames(fnames);
	if (get_cmd(mini, cmd, toparse))
		return (1);
	cmd->builtin = (*cmd->cmd && (!ft_strncmp(*cmd->cmd, "echo", -1)
				|| !ft_strncmp(*cmd->cmd, "export", -1)
				|| !ft_strncmp(*cmd->cmd, "exit", -1)
				|| !ft_strncmp(*cmd->cmd, "cd", -1) || !ft_strncmp(*cmd->cmd,
					"env", -1) || !ft_strncmp(*cmd->cmd, "pwd", -1)
				|| !ft_strncmp(*cmd->cmd, "unset", -1)));
	if (cmd->builtin && mini->oldpipe[0] == -1 && mini->newpipe[0] == -1
		&& mini->oldpipe[1] == -1 && mini->newpipe[1] == -1)
		cmd->fork = 0;
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
	parse_wdcard_again(&toparse, &mini->err, &mini->exc);
	//parse_wdcard_again(&cmd->redir, &mini->err, &mini->exc);
	if (split_words(mini, &toparse) || split_words(mini, &cmd->redir))
	{
		ft_lstclear(&cmd->redir, &free_lexec);
		ft_lstclear(&toparse, &free_lexec);
		return (1);
	}
	return (parse_cmd_txt(mini, toparse, cmd, has_wdcard));
}
