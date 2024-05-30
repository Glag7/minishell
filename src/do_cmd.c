/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:31:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/30 19:19:43 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_redir_out(t_mini *mini, int *inout, int err_)
{
	int	err;

	err = err_;
	if (inout[1] != -1)
	{
		err |= dup2(1, inout[1]);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n")
		close(inout[1]);
	}
	else if (mini->oldpipe[1] != -1)
	{
		err |= dup2(1, oldpipe[1]);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n")
	}
	if (err)
	{
		mini->err = ERR_SHUTUP;
		mini->exc = 2;
	}
	close_pipes(mini);
	return (err);
}

static int	dup_redir(t_mini *mini, int *inout)
{
	int	err;

	err = 0;
	if (inout[0] != -1)
	{
		err |= dup2(0, inout[0]);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n")
		close(inout[0]);
	}
	else if (mini->oldpipe[0] != -1)
	{
		err |= dup2(0, oldpipe[0]);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n")
	}
	return (dup_redir_out(mini, inout, err));
}

void	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	inout[2];

	if (open_redir(mini, cmd->redir, inout))
		return ;
	//signaux ? peu etre
	//penser a exc
	//redir + hdoc
	//builtin
	return ;
}

void	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*path;
	int	inout[2];

	path = NULL;
	if (open_redir(mini, cmd->redir, inout) || dup_redir(mini, inout))
		return ;
	if (get_path(mini, cmd->cmd, &path))
		return ;
	sig_mode(SIG_EXEC);
	execve(path, cmd->cmd, mini->envp.envp);
	ft_perror("minishell: execve: ", strerror(errno), "\n");
	sig_mode(SIG_IGNORE);
	free(path);
	mini->err = ERR_SHUTUP;
}
