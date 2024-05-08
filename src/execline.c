/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/08 19:23:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execfork(t_mini *mini, t_list **exec, int in, int out)
{
	t_list	*tmp;

	*exec = (*exec)->next;
	tmp = ft_lstnew(NULL);
	if (tmp == NULL)
	{
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		return ;
	}
	ft_lstadd_back(&mini->pid, tmp);
	tmp->num = fork();//chercher pipe
	if (tmp->num == -1)
	{
		ft_perror3("minishell: fork: ", strerror(errno), "\n");
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
	}
	else if (tmp->num == 0)
	{
		mini->forked = 1;
		execline(mini, *exec, in, out);
		if (mini->err == 0)
			mini->err = ERR_SHUTUP;
	}
	*exec = find_next_op(*exec);
}

void	execline(t_mini *mini, t_list *exec, int in, int out)
{
	ft_lstclear(&mini->pids, NULL);
	while (exec && !(((t_tok *)exec->content)->tok == PAR
			&& ((t_tok *)exec->content)->type == CLOSE)
			&& !mini->err)
	{
		if (((t_tok *)exec->content)->tok == PAR)
			execfork(mini, &exec, in, out);
		else
		{
			//exec
		}
	}
	//si err == 0 ou err == bye
	//mettre exc a jour
	//pids peut leak, il faut les attendre
	//changer exc ou pas en fonction de l'erreur
}
