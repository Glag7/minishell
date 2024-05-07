/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/07 20:13:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline()
{
	//TODO, parsing des pipelines, remplacement des variables des hdocs
	//if (mini->err == 0)
	//{
	//sig_mod(SIG_EXEC)//pas ici
	//start_exec
	//sig_mode(SIG_IGNORE);
	//}
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

void	execline(t_mini *mini, t_list *exec)
{
	exit(hdoc_replace(mini, ((t_tok *)exec->content)->hdoc));//
	if (((t_tok *)exec->content)->tok == PAR)
	{
		//find end
		//if pipe pipe
		//else exit code
		//start fork
	}
}
