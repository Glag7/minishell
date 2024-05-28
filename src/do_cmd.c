/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:31:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/28 19:16:36 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (open_redir(mini, cmd->redir, inout))// || dup_redir(mini, inout))//redir sinon pipes
		return ;
	if (get_path(mini, cmd->cmd, &path))
	{
		if (inout[0] != -1)
			close(inout[0]);
		if (inout[1] != -1)
			close(inout[0]);
		return ;
	}
	sig_mode(SIG_EXEC);
	execve(path, cmd->cmd, mini->envp.envp);
	ft_perror("minishell: execve: ", strerror(errno), "\n");
	sig_mode(SIG_IGNORE);
	free(path);
	if (inout[0] != -1)
		close(inout[0]);
	if (inout[1] != -1)
		close(inout[0]);
	mini->err = ERR_SHUTUP;
}
