/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/03 17:04:27 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*increment_shlvl(char *old_shlvl)
{
	long	n_lvl;
	char	*lvl;
	char	*new_shlvl;

	n_lvl = ft_atoi(&old_shlvl[6]) + 1;
	lvl = ft_itoa(n_lvl);
	if (lvl == NULL)
	{
		ft_perror(MSG_MALLOC);
		return (NULL);
	}
	if (n_lvl >= 1000)
	{
		ft_perror("minishell: warning: shell level (");
		ft_perror(lvl);
		ft_perror(") too high, resetting to 1\n");
		new_shlvl = ft_strdup("SHLVL=1");
	}
	else
		new_shlvl = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (new_shlvl);
}

static int	check_numeric(char *str)// renvoie 0 si pas digit, plus de 1 - ou +, > int64_t max ; peut avoir des ws devant, un - ou un +
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_is(str[i], DIGIT) != 0)
	{
		nbr = 10 * nbr + str[i] - 48;
		if (nbr < 0)
			return (0);
		i++;
	}
	return (str[i] == '\0');
}

//SHLVL : si pas declare ou pas init ou pas numerique ou vide : mis a 1
//        si negatif ou > int32_t max : mis a 0
//        si positif : incremente de 1
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
	if (*old_shlvl == NULL || ft_strlen(*old_shlvl) <= 6
		|| check_numeric(*old_shlvl) == 0)//pb: valide avec plus grand que int max alors que ca devrait pas
		new_shlvl = ft_strdup("SHLVL=1");
	else if ((*old_shlvl)[len_until_char(*old_shlvl, '=') + 1] == '-'
		|| ft_atoi(*old_shlvl) > 2147483647)
		new_shlvl = ft_strdup("SHLVL=0");
	else
		new_shlvl = increment_shlvl(*old_shlvl);
	if (new_shlvl == NULL)
	{
		ft_perror(MSG_MALLOC);
		return (1);
	}
	free(*old_shlvl);
	*old_shlvl = new_shlvl;
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
		remove_var(envp, "OLDPWD", free);
	return (0);
}

//PWD initialise avec getcwd()
static int	check_pwd_shlvl(char ***envp_ptr, size_t len)
{
	char	*new_pwd;
	char	*pwd;
	char	**old_pwd;

	(*envp_ptr)[len + 1] = NULL;
	(*envp_ptr)[len + 2] = NULL;
	(*envp_ptr)[len + 3] = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_perror(MSG_MALLOC);
		return (ERR_AINTNOWAY);
	}
	new_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
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
}

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
	return (check_pwd_shlvl(envp_ptr, len));
}
