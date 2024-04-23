/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:03:21 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/23 20:15:58 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	selection_sort(void **arr, size_t len, char cmp(char *, char *))
{
	void	*swap;
	size_t	i;
	size_t	i_min;
	size_t	i_sorted;

	i_sorted = 0;
	while (i_sorted < len)
	{
		i = i_sorted;
		i_min = i_sorted;
		while (i < len)
		{
			if (cmp(arr[i_min], arr[i]) > 0)
				i_min = i;
			i++;
		}
		swap = arr[i_sorted];
		arr[i_sorted] = arr[i_min];
		arr[i_min] = swap;
		i_sorted++;
	}
}

static char	**sort_envp(char **envp)
{
	char	**sorted;
	size_t	len;
	size_t	i;

	len = 0;
	while (envp[len] != NULL)
		len++;
	sorted = malloc((len + 1) * sizeof(char *));
	if (sorted == NULL)
		return (NULL);
	sorted[len] = NULL;
	i = 0;
	while (i < len)
	{
		sorted[i] = envp[i];
		i++;
	}
	selection_sort((void **)sorted, len, strgreater);
	return (sorted);
}

static char	export_only(char **envp)
{
	char	**sort;
	size_t	i;
	size_t	len;

	i = 0;
	sort = sort_envp(envp);
	if (sort == NULL)
		return (2);
	while (sort[i] != NULL)
	{
		len = len_until_char(sort[i], '=');
		if (write(1, "declare -x ", 11) == -1 || write(1, sort[i], len) == -1)
		{
			free(sort);
			return (1);
		}
		if (sort[i][len] == '=' && (write(1, "=\"", 2) == -1
				|| write(1, &sort[i][len + 1], ft_strlen(&sort[i][len + 1])) == -1
				|| write(1, "\"", 2) == -1))
		{
			free(sort);
			return (1);
		}
		if (write(1, "\n", 1) == -1)
		{
			free(sort);
			return (1);
		}
		i++;
	}
	free(sort);
	return (0);
}

//invalid if not alnum OR if it starts with a num
static char	check_syntax(char *var)
{
	size_t	i;

	if (ft_is(ALPHA, var[0]) == 0)
	{
		ft_perror("minishell: export: '");
		ft_perror(var);
		ft_perror("': not a valid identifier\n");
		return (1);
	}
	i = 0;
	while (ft_is(ALNUM, var[i]) != 0)
		i++;
	if (var[i] != 0 && var[i] != '=' && var[i] != '+' && var[i + 1] != '=')
	{
		ft_perror("minishell: export: '");
		ft_perror(var);
		ft_perror("': not a valid identifier\n");
		return (1);
	}
	return (0);
}

static char	check_existence(char *var, char **envp)
{
	size_t	len_name;
	char	**ptr;
	char	c;

	len_name = 0;
	while (ft_is(ALNUM, var[len_name]) != 0)
		len_name++;
	c = var[len_name];
	var[len_name] = '\0';
	ptr = get_var(envp, var);
	var[len_name] = c;
	if (ptr == NULL)
		return (0);
	return (1);
}

static char	create_var(char *var, char ***envp)
{
	char	**new_envp;
	char	**old_envp;
	size_t	len;
	size_t	i;

	old_envp = *envp;
	len = 0;
	while (old_envp[len] != NULL)
		len++;
	new_envp = malloc((len + 2) * sizeof(char *));
	if (new_envp == NULL)
		return (2);
	new_envp[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(var);
	if (new_envp[i] == NULL)
	{
		free(new_envp);
		return (2);
	}
	free(old_envp);
	*envp = new_envp;
	return (0);
}

//realloc new var
static char	overwrite_var()
{
	
	return (0);
}

//realloc new var
static char	concatenate_var()
{
	
	return (0);
}

//for each var : if invalid : continue; else : if nonexistant : create_var; else : if = : overwrite_var; else if += : concatenate_var;
static char	update_envp(char **argv, char ***envp)
{
	size_t	i;
	char	error;
	char	*arg;

	error = 0;
	i = 0;
	arg = argv[0];
	while (arg != NULL)
	{
		if (check_syntax(arg) == 0)
		{
			if (check_existence(arg, *envp) == 0)
				error |= create_var(arg, envp);
			else if (arg[len_until_char(arg, '=')] == '='
				&& arg[len_until_char(arg, '=') - 1] == '+')
				error |= concatenate_var(arg, envp);
			else
				error |= overwrite_var(arg, envp);
			if (error & 2 != 0)
				return (2);
		}
		i++;
		arg = argv[i];
	}
	return (0);
}

int	builtin_export(int argc, char **argv, char ***envp)// gerer export solo, puis check syntaxe, puis gerer creation, ecrasement et concatenation
{
	int	error;

	if (argc <= 1)
	{
		error = (int)export_only(*envp);
		if (error == 2)
			ft_perror("minishell: export: malloc: failed memory allocation\n");
		return (error);
	}
	if (check_syntax(&argv[1]))
		return (1);
	error = (int)update_envp(&argv[1], envp);
	if (error == 2)
		ft_perror("minishell: export: malloc: failed memory allocation\n");
	return (error);
}
