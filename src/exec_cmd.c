/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:03:39 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/16 12:50:09 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_cmd_fork(t_mini *mini, t_cmd *cmd)
{
	ft_lstclear(&mini->pids, NULL);
	mini->forked = 2;
	if ((mini->oldpipe[READ] != -1 && dup2(mini->oldpipe[READ], 0) == -1)
		|| (mini->newpipe[WRITE] != -1 && dup2(mini->newpipe[WRITE], 1) == -1))
	{
		ft_perror3("minishell: dup2: ", strerror(errno), "\n");
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
	}
	close_pipes(mini);
	if (cmd->builtin)
		do_builtin(mini, cmd);
	else
		do_cmd(mini, cmd);
	if (mini->err == 0)
		mini->err = ERR_BYEBYE;
}

static void	cmd_fork(t_mini *mini, t_list **exec, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = ft_lstnew(NULL);
	if (tmp == NULL)
	{
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		return ;
	}
	ft_lstadd_back(&mini->pids, tmp);
	tmp->num = fork();
	if (tmp->num == -1)
	{
		ft_perror3("minishell: fork: ", strerror(errno), "\n");
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
	}
	else if (tmp->num == 0)
		manage_cmd_fork(mini, cmd);
	else
		*exec = find_next_op(*exec);
}

void	exec_cmd(t_mini *mini, t_list **exec)
{
	t_cmd	cmd;

	cmd = (t_cmd){0, 0, 0, 0};
	if (parse_cmd(mini, *exec, &cmd))
		return ;
	if (cmd.fork)
		cmd_fork(mini, exec, &cmd);
	else
	{
		do_builtin(mini, &cmd);
		*exec = find_next_op(*exec);
	}
	if (cmd.cmd)
		ft_freearr(cmd.cmd);
	ft_lstclear(&cmd.redir, &free_lredir);
}
