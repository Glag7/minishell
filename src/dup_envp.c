/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/02 17:57:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*increment_shlvl(char *old_shlvl)
{
	char	*new_shlvl;

	;
	return (new_shlvl);
}

static int	()
{
	
}

//SHLVL : si pas declare ou pas init ou pas numerique ou vide : mis a 1
//        si negatif ou overflow : mis a 0
//        si positif : incremente de 1
//SHLVL max : 1000 ; if SHLVL would become 1000 or higher, warning + reset to 1
//'pas numerique' = < 0 ou > 9 ou ++ ou -- (tout ce qui passerai pas un atoi en fait)
//'numerique' = peut avoir des whitespaces devant, et un + ou un -
static int	update_shlvl(char **envp, size_t *len)
{
	char	**old_shlvl;
	char	*new_shlvl;

	old_shlvl = get_var(envp, "SHLVL");
	if (old_shlvl == NULL)
	{
		old_shlvl = &envp[*len];
		(*len)++;
	}
	if (*old_shlvl == NULL || ft_strlen(*old_shlvl) <= 6 || PAS NUMERIQUE || >= 1000)
		new_shlvl = ft_strdup("SHLVL=1");
	else if (new_shlvl && ((*old_shlvl)[len_until_char(*old_shlvl, '=') + 1] == '-'
			|| OVERFLOW))
		new_shlvl[6] = '0';
	else
		new_shlvl = increment_shlvl(*old_shlvl);
	if (new_shlvl == NULL)
	{
		ft_perror(MSG_MALLOC);
		return (1);
	}
	if (replace_var(envp, new_shlvl, "SHLVL") == 1)
		;//ajouter a la fin
	return (0);
}

//OLDPWD : si pas declare ou pas init : il est declare
//         si init mais son chemin n'existe pas : il est supprime
//         si init et chemin existe : il est conserve tel quel
static int	update_oldpwd(char **envp, size_t *len)
{
	char	**old_oldpwd;

	old_oldpwd = get_var(envp, "OLDPWD");
	if (old_oldpwd == NULL)
	{
		old_oldpwd = &envp[*len];
		(*len)++;
	}
	if (*old_oldpwd == NULL)
	{
		*old_oldpwd = ft_strdup("OLDPWD");
		if (*old_oldpwd == NULL)
		{
			ft_perror(MSG_MALLOC);
			return (1);
		}
	}
	else if (ft_strlen(*old_oldpwd) > 6
		&& access(&(*old_oldpwd)[len_until_char(*old_oldpwd, '=') + 1], F_OK) == -1)
		remove_var(envp, "OLDPWD");
	return (0);
}

//PWD initialise avec getcwd()
static int	check_pwd_shlvl(char ***envp_ptr, size_t len)
{
	char	*new_pwd;

	(*envp_ptr)[len + 1] = NULL;
	(*envp_ptr)[len + 2] = NULL;
	(*envp_ptr)[len + 3] = NULL;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		ft_perror(MSG_MALLOC);
		return (ERR_AINTNOWAY);
	}
	old_pwd = get_var(*envp_ptr, "PWD");
	if (old_pwd != NULL)
	{
		free(*old_pwd);
		*old_pwd = new_pwd;
	}
	else
		(*envp_ptr)[len++] = new_pwd;
	if (update_oldpwd(*envp_ptr, &len) != 0)
		return (ERR_AINTNOWAY);
	if (update_shlvl(*envp_ptr, &len) != 0)
		return (ERR_AINTNOWAY);
	return (0);
}*/

int	dup_envp(char ***envp_ptr)
{
	char	**envp;
	size_t	len;
	size_t	i;

	envp = *envp_ptr;
	len = 0;
	while (envp[len] != NULL)
		len++;
	*envp_ptr = malloc((len + 4) * sizeof(char *));
	if (*envp_ptr == NULL)
		return (ERR_AINTNOWAY);
	(*envp_ptr)[len] = NULL;
	i = 0;
	while (i < len)
	{
		(*envp_ptr)[i] = ft_strdup(envp[i]);
		if ((*envp_ptr)[i] == NULL)
		{
			ft_freearr(envp);
			*envp_ptr = NULL;
			return (ERR_AINTNOWAY);
		}
		i++;
	}
	return (0);//check_pwd_shlvl(envp_ptr, len));
}
