/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 14:00:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline()
{
	/*
	//while //par_open skip

	//pour chaque pipe
	//vars
	//word splitting
	//redirs
	//wdcards
	//replace var hdoc
	//do pipe if needed
	//do hdoc + redirs
	//extract cmand
	//do cmand
	//check sigsegv ?*/
	return (0);
}

//avant chaque pipeline gnl parse_quote, parse_var, strjoin (mieux), write

void	execline(t_mini *mini)
{
	mini->hdocs = NULL;
	fill_heredocs(mini->exec, mini);//SIGNAUX
	//if (mini->err == 0)
	//start_exec
	if (mini->forked == 0)
		ft_lstclear(&mini->hdocs, &wrap_unlink);
	else
		ft_lstclear(&mini->hdocs, NULL);
}
