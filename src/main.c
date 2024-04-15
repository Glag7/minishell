/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/15 14:26:08 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig = 0;

void	debug(void *slice_)
{
	t_quote	*slice;

	slice = slice_;
	printf("=====\n\"%.*s\"\nlen:\t%4zu\nqtype:\t%4d\n=====\n",
		(int)slice->str.len, slice->str.s, slice->str.len, slice->qtype);
	free(slice);
}

static int	*parse_line(char *s, int *err, int *exc)
{
	t_list	*tmp;

	tmp = parse_quotes(s, err, exc);
	//check ctrl c
	if (*exc)
		return (NULL);
	//tmp = parse_par(tmp, err);
	//parsing
	//ctrl c
	
	ft_lstclear(&tmp, debug);
	return (0);
}

static void	exec_line(char *s, int *err, int *exc)
{
	int	*tree;//no

	tree = parse_line(s, err, exc);
	//check ctrl c
	//gestion erreur
	//exec
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	int	err;
	int	exit_code;

	while (1)
	{
		err = 0;
		exit_code = 0;
		s = readline("coquillage de petite taille > ");
		if (s == NULL)
			break ;
		if (*s)
		{
			exec_line(s, &err, &exit_code);
			add_history(s);
		}
		free(s);
		if (err)
			break ;
	}
	rl_clear_history();
	return (exit_code);
}
