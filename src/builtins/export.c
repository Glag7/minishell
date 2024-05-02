/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:03:21 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/26 16:03:36 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_syntax(char *var)
{
	size_t	i;

	if (ft_is(ALPHA, var[0]) == 0 && var[0] != '_')
	{
		ft_perror("minishell: export: '");
		ft_perror(var);
		ft_perror("': not a valid identifier\n");
		return (1);
	}
	i = 0;
	while (ft_is(ALNUM, var[i]) != 0 || var[i] == '_')
		i++;
	if (var[i] == 0 || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (0);
	ft_perror("minishell: export: '");
	ft_perror(var);
	ft_perror("': not a valid identifier\n");
	return (1);
}

char	check_existence(char *var, char **envp)
{
	size_t	len_name;
	char	**old_var;
	char	c;

	len_name = 0;
	while (ft_is(ALNUM, var[len_name]) != 0)
		len_name++;
	c = var[len_name];
	var[len_name] = '\0';
	old_var = get_var(envp, var);
	var[len_name] = c;
	if (old_var == NULL)
		return (0);
	return (1);
}

int	builtin_export(int argc, char **argv, t_envp *envp_status)
{
	int	error;

	if (argc <= 1)
	{
		error = (int)export_only(*envp_status);
		if (error == 2)
			ft_perror("minishell: export: malloc(): \
			failed memory allocation\n");
		return (error);
	}
	error = (int)export_to_envp(&argv[1], envp_status);
	if (error == 2)
		ft_perror("minishell: export: malloc(): failed memory allocation\n");
	return (error);
}
