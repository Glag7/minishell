/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/09 19:17:47 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(void *slice_)
{
	t_quote	*slice;

	slice = slice_;
	printf("=====\n\"%.*s\"\nlen:\t%4zu\nqtype:\t%4d\n=====\n",
		(int)slice->str.len, slice->str.s, slice->str.len, slice->qtype);
	free(slice);
}

static int	parse_line(char *s, int *err)
{
	t_list	*tmp;

	tmp = parse_quotes(s, err);
	if (*err == ERR_PARSE)
	{
		ft_perror(MSG_QUOTE);
		ft_lstclear(&tmp, debug);
		*err = 0;
		return (0);
	}
	if (*err == ERR_AINTNOWAY)
		return (ERR_AINTNOWAY);
	//parsing
	
	ft_lstclear(&tmp, debug);
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
		err = exec_line(s);
		add_history(s);
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
