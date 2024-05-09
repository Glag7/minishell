/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/09 15:40:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execfork(t_mini *mini, t_list **exec)
{
	t_list	*tmp;

	//get new pipe
	*exec = (*exec)->next;
	tmp = ft_lstnew(NULL);
	if (tmp == NULL)
	{
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		return ;
	}
	ft_lstadd_back(&mini->pids, tmp);
	tmp->num = fork();//chercher pipe
	if (tmp->num == -1)
	{//dup2
		ft_perror3("minishell: fork: ", strerror(errno), "\n");
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
	}
	else if (tmp->num == 0)
	{
		mini->forked = 1;
		execline(mini, *exec);
		if (mini->err == 0)
			mini->err = ERR_SHUTUP;
	}
	//*exec = find_next_op(*exec);
}//FERMER PIPES EHEN ERREUR

void	execline(t_mini *mini, t_list *exec)
{
	ft_lstclear(&mini->pids, NULL);
	while (exec && !(((t_tok *)exec->content)->tok == PAR
			&& ((t_tok *)exec->content)->type == CLOSE)
		&& !mini->err && !update_pipes(mini, exec))
	{
		if (((t_tok *)exec->content)->tok == PAR)
			execfork(mini, &exec);
		if (((t_tok *)exec->content)->tok == OP)
		{
			//
		}
		else
		{
			//exec
		}
	}
	close_pipes(mini);
	waitall(mini);
}
