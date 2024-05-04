/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:06:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 13:29:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline()
{
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
	//check sigsegv ?
	return (0);
}

//avant chaque pipeline gnl parse_quote, parse_var, strjoin (mieux), write

void	execline(t_list *toexec, int *err, int *exc, t_envp *envp)
{
	t_list	*hdocs = NULL;
	if (fill_heredocs(toexec, &hdocs, exc, err))//SIGNAUX
		return ;
	//faire exec dans une autre fonction les hdocs sont a part
	//unlink les hdocs
	exec_pipeline();
	return ;
}
