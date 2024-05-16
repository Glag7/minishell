/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/09 20:06:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_fork(t_mini *mini, t_list **exec)
{
	*exec = (*exec)->next;
	ft_lstclear(&mini->pids, NULL);
	mini->forked = 1;
	if ((mini->oldpipe[READ] != -1 && dup2(mini->oldpipe[READ], 0) == -1)
		|| (mini->newpipe[WRITE] != -1 && dup2(mini->newpipe[WRITE], 1) == -1))
	{
		ft_perror3("minishell: dup2: ", strerror(errno), "\n");
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
	}
	close_pipes(mini);
}

static void	execfork(t_mini *mini, t_list **exec)
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
		manage_fork(mini, exec);
	else
		*exec = find_next_op(*exec);
}

void	execline(t_mini *mini, t_list *exec)
{
	while (exec && !(((t_tok *)exec->content)->tok == PAR
			&& ((t_tok *)exec->content)->type == CLOSE)
		&& !mini->err && !update_pipes(mini, exec))
	{
		if (((t_tok *)exec->content)->tok == PAR)
			execfork(mini, &exec);
		else if (((t_tok *)exec->content)->tok == OP)
		{
			waitall(mini);
			exec = find_next_op_type(exec, !!mini->exc);
			if (exec)
				exec = exec->next;
		}
		else
			exec_cmd(mini, &exec);
	}
	close_pipes(mini);
	waitall(mini);
}
