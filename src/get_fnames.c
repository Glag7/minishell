/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fnames.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:38:58 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/20 17:49:12 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fnames(t_mini *mini, t_str **fnames)
{
	DIR		*dir;
	struct dirent	curr;

	dir = opendir(".");
	if (dir == NULL)
	{
		ft_perror3("minishell: opendir: ", strerror(errno), "\n");
		mini->err = ERR_SHUTUP;
		mini->exc = 2;
		return (1);
	}
	closedir(dir);
	return (0);
}
