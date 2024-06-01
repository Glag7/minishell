/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_alloc_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:35:07 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/31 13:57:52 by ttrave           ###   ########.fr       */
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

static size_t	count_new_len(char **argv, char **envp, int *error)
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
			if (check_syntax(arg) == 1)
			{
				*error = 1;
				ft_perror3("minishell: export: '", arg,
					"': not a valid identifier\n");
			}
		}
		arg = argv[++i];
	}
	return (len);
}

int	export_to_envp(char **argv, t_envp *envp_status)
{
	size_t	new_len;
	char	**new_envp;
	int		error;

	error = 0;
	new_len = count_new_len(argv, envp_status->envp, &error);
	new_envp = malloc((new_len + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	new_envp[new_len] = NULL;
	if (update_envp(new_envp, argv, envp_status, new_len) == 1)
	{
		ft_freearr(new_envp);
		return (2);
	}
	if (g_sig == ENOENT)
	{
		ft_freearr(new_envp);
		return (130);
	}
	ft_freearr(envp_status->envp);
	envp_status->envp = new_envp;
	return (error);
}
