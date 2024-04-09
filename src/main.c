/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/09 16:54:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_line(char *s, int *err)
{
	int		err;
	t_list	*tmp;

	tmp = parse_quotes(s, &err);
	if (err == ERR_PARSE)
	{
		ft_lstfree(&tmp, NULL);
		return (0);
	}
	if (err == ERR_AINTNOWAY)
		return (ERR_AINTNOWAY);
	//parsing
	return (0);
}

static int	exec_line(char *s)
{
	int	err;
	int	tree;//no

	tree = parse_line(s, &err);
	//gestion erreur
	//exec
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	int	err;

	while (1)
	{
		s = readline("coquillage de petite taille > ");
		if (s == NULL)
			break ;
		if (!*s)
			continue ;
		add_history(s);
		err = exec_line(s);
		free(s);
		if (err)
		{
			rl_clear_history();
			exit(err);
		}
	}
	rl_clear_history();
	return (0);
}
