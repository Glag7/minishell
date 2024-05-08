/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:47:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/07 16:25:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrap_unlink(void *name)
{
	unlink((char *)name);
}

void	wrap_freearr(void *envp)
{
	if (envp)
		ft_freearr(envp);
}
