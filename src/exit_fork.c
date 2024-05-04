/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:38:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 17:03:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fork(t_list *lexec, char **envp, int exc)
{
	ft_lstclear(&lexec, &free_lexec);
	ft_freearr(envp);
	close(0);
	close(1);
	close(2);
	exit(exc);
}
