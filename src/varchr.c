/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:43:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/10 16:01:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	varchr(t_str s, char **envp)
{
	if (!envp)
		return ((t_str){0, 0});
	while (*envp)
	{
		if (ft_strncmp(s.s, *envp, s.len) == 0
			&& (*envp)[s.len] == '=')
			return ((t_str){envp[0] + s.len + 1,
				ft_strlen(*envp) - s.len - 1});
		envp++;
	}
	return ((t_str){0, 0});
}
