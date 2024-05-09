/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:03:39 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/09 20:07:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si erreur close pipes !!!!!!!!!!!!!!!
void	exec_cmd(t_mini *mini, t_list **exec)
{
	*exec = (*exec)->next;//rm
	//exec if pipe before && pipe after etc
	//parsing, fork ou pas
	//signaux
	//redir
	//exec

}
