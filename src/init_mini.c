/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:12:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 17:25:03 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	mini->exc = 0;
	mini->forked = 0;
	if (isatty(0))
		mini->prompt = "coquillage de petite taille > ";
	else
		mini->prompt = NULL;
	mini->err = dup_envp(&envp);
	mini->envp = (t_envp) {envp, 1, 1};
	if (mini->err == 0)
		mini->err = 0;//sig_handler
}
