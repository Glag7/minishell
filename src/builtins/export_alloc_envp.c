/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_alloc_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:35:07 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/29 19:25:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static size_t	new_arg(char **argv, size_t i)
{
	size_t	j;
	size_t	len;
	size_t	len_cmp;
	char	*arg;
	char	*arg_cmp;

	arg_cmp = argv[i];
	len_cmp = len_until_char(arg_cmp, '=');
	if (arg_cmp[len_cmp - 1] == '+')
		len_cmp--;
	j = 0;
	arg = argv[j];
	while (j < i)
	{
		len = len_until_char(arg, '=');
		if (arg[len - 1] == '+')
			len--;
		if (len_cmp > len)
			len = len_cmp;
		if (ft_strncmp(arg, arg_cmp, len) == 0)
			return (1);
		j++;
		arg = argv[j];
	}
	return (0);
}

static size_t	count_new_len(char **argv, char **envp)
{
	size_t	len;
	size_t	i;
	char	*arg;

	len = 0;
	while (envp[len] != NULL)
		len++;
	i = 0;
	arg = argv[0];
	while (arg != NULL)
	{
		if (check_existence(arg, envp) == 1)
		{
			if (check_syntax(arg) == 0 && new_arg(argv, i) == 0)
				len++;
			else if (new_arg(argv, i) == 0)
			{
				ft_perror("minishell: export: '");
				ft_perror(arg);
				ft_perror("': not a valid identifier\n");
			}
		}
		arg = argv[++i];
	}
	return (len);
}

static int	copy_envp(char **new_envp, char **old_envp, size_t len)
{
	size_t	i;
	char	*old_var;

	i = 0;
	old_var = old_envp[0];
	while (old_var != NULL)
	{
		new_envp[i] = ft_strdup(old_var);
		if (new_envp[i] == NULL)
			return (1);
		i++;
		old_var = old_envp[i];
	}
	while (i < len)
	{
		new_envp[i] = NULL;
		i++;
	}
	return (0);
}

int	export_to_envp(char **argv, t_envp *envp_status)
{
	size_t	new_len;
	char	**new_envp;

	new_len = count_new_len(argv, envp_status->envp);
	new_envp = malloc((new_len + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	new_envp[new_len] = NULL;
	if (update_envp(new_envp, argv, envp_status, new_len) == 1)
	{
		ft_freearr(new_envp);
		return (2);
	}
	if (g_sig == 2)
	{
		ft_freearr(new_envp);
		return (130);
	}
	ft_freearr(envp_status->envp);
	envp_status->envp = new_envp;
	return (0);
}
