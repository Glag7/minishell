/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/01 19:34:11 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PWD initialise avec getcwd
//OLDPWD : si pas declare ou pas init : il est declare
//         si init mais son chemin n'existe pas : il est supprime
//         si init et chemin existe : il est conserve tel quel
//SHLEVEL : si pas declare ou pas init ou pas numerique : mis a 1
//          si init et negatif : mis a 0
//          si init et positif : incremente de 1
static int	check_pwd_shlvl(char ***envp_ptr, size_t len)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		ft_perror("minishell : getcwd() : malloc() : memory allocation failed\n");
		return (ERR_AINTNOWAY);
	}
	old_pwd = get_var(*envp_ptr, "PWD");
	if (old_pwd != NULL)
	{
		free(*old_pwd);
		*old_pwd = new_pwd;
	}
	else
		(*envp_ptr)[len] = new_pwd;
	// SHLVL et OLPWD
	return (0);
}

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
	*envp_ptr = malloc((i + 4) * sizeof(char *));
	if (*envp_ptr == NULL)
		return (ERR_AINTNOWAY);
	(*envp_ptr)[i] = NULL;
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
	return (check_pwd_shlvl(envp_ptr, i));
}
