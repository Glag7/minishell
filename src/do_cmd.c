/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:31:36 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/20 17:28:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_builtin(t_mini *mini, t_cmd *cmd)
{
	//signaux ? peu etre
	//penser a exc
	//redir + hdoc
	//builtin
	return ;
}

void	do_cmd(t_mini *mini, t_cmd *cmd)
{
	//signaux, si erreur siignore ?
	//redir + hdoc
	//redir: if name[0] == NULL || name[1] != NULL : bomba
	//execve + exc
	//erreur
	return ;
}
