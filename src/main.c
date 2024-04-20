/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/20 17:37:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	debug(void *tok_)
{
	t_tok	*tok;
	t_quote	slice;

	tok = tok_;
	if (tok->tok == UNDEF)
	{
		slice = tok->quote;
		printf("=====\n\"%.*s\"\nlen:\t%4zu\nqtype:\t%4d\n=====\n",
			(int)slice.str.len, slice.str.s, slice.str.len, slice.qtype);

	}
	free(tok);
}

static int	*parse_line(char *s, int *err, int *exc)
{
	t_list	*tmp;

	tmp = parse_quotes(s, err, exc);
	if (tmp == NULL && g_sig == 0)
		return (NULL);
	tmp = parse_pars(tmp, err, exc);
	//parse && || |
	//<<
	//parse $
	//parse *
	//parse > < >>
	
	if (g_sig == SIGINT)
	{
		*exc = 128 + SIGINT;
		ft_lstclear(&tmp, &free);
	}
	ft_lstclear(&tmp, &debug);
	return (tmp);
}

static void	exec_line(char *s, int *err, int *exc)
{
	int	*tree;//no

	tree = parse_line(s, err, exc);
	//check ctrl c
	//gestion erreur (check null)
	//exec
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	int	err;
	int	exit_code;

	//sig handler
	err = 0;
	exit_code = 0;
	while (1)
	{
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
