/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/01 17:42:15 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PWD, le creer
//SHLEVEL, si existe pas mis a 1, si negatif mis a 0

int	dup_envp(char ***envp_ptr)
{
	char	**envp;
	size_t	i;
	size_t	j;

	envp = *envp_ptr;
	i = 0;
	j = -1;
	while (envp[i])
		i++;
	*envp_ptr = malloc((i + 3) * sizeof(char *));
	if (*envp_ptr == NULL)
		return (ERR_AINTNOWAY);
	while (++j < i)
	{
		(*envp_ptr)[j] = ft_strdup(envp[j]);
		if ((*envp_ptr)[j] == NULL)
		{
			ft_freearr(envp);
			*envp_ptr = NULL;
			return (ERR_AINTNOWAY);
		}
	}
	(*envp_ptr)[j] = NULL;
	return (check_pwdshlevel(envp));
}
