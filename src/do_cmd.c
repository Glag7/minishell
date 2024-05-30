/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:31:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/30 23:25:25 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_redir_out(t_mini *mini, int *inout, int err_)
{
	int	err;

	err = err_;
	if (!err && inout[1] != -1)
	{
		err |= dup2(inout[1], 1);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n");
	}
	else if (!err && mini->newpipe[1] != -1)
	{
		err |= dup2(mini->newpipe[1], 1);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n");
	}
	if (err)
	{
		mini->err = ERR_SHUTUP;
		mini->exc = 2;
	}
	close_pipes(mini);
	if (inout[1] != -1)
		close(inout[1]);
	if (inout[0] != -1)
		close(inout[0]);
	return (err);
}

static int	dup_redir(t_mini *mini, int *inout)
{
	int	err;

	err = 0;
	if (inout[0] != -1)
	{
		err |= dup2(inout[0], 0);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n");
	}
	else if (mini->oldpipe[0] != -1)
	{
		err |= dup2(mini->oldpipe[0], 0);
		if (err)
			ft_perror3("minishell: dup2: ", strerror(errno), "\n");
	}
	return (dup_redir_out(mini, inout, err));
}

void	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	inout[2];

	if (open_redir(mini, cmd->redir, inout))
		return ;
	if (inout[0] == -1)
		inout[0] = mini->oldpipe[0];
	if (inout[0] == -1)
		inout[0] = 0;
	if (inout[1] == -1)
		inout[1] = mini->newpipe[1];
	if (inout[1] == -1)
		inout[1] = 1;
	//sig builtin
	wrap_builtin(mini, cmd->cmd, inout);
	//sig builtin
	if (inout[0] != -1 && inout[0] != 0)
		close(inout[0]);
	if (inout[1] != -1 && inout[1] != 1)
		close(inout[1]);
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
	ft_perror3("minishell: execve: ", strerror(errno), "\n");
	sig_mode(SIG_IGNORE);
	free(path);
	mini->err = ERR_SHUTUP;
	mini->exc = 126;
}
