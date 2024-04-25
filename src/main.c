/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/25 16:07:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	debug(void *tok_)
{
	t_tok		*tok;
	t_quote		slice;
	static char	*yesno[2] = {"NO", "YES"};

	tok = tok_;
	if (tok->tok == UNDEF)
	{
		slice = tok->quote;
		printf("=====\n\"%.*s\"\nLEN:\t%4zu\nQTYPE:\t%4d\n=====\n",
			(int)slice.str.len, slice.str.s, slice.str.len, slice.qtype);
	}
	else if (tok->tok == PAR)
	{
		if (tok->type == CLOSE)
			printf("=====\nPAR_CLOSE:\t)\n=====\n");
		else
			printf("=====\nPAR_OPEN:\t(\n=====\n");
	}
	else if (tok->tok == PIPE)
		printf("=====\nPIPE:\t|\n=====\n");
	else if (tok->tok == OP)
	{
		if (tok->type == AND)
			printf("=====\nOP_AND:\t&&\n=====\n");
		else
			printf("=====\nOP_OR:\t||\n=====\n");
	}
	else if (tok->tok == HDOC)
	{
		printf("=====\nHDOC:\t<<\nLIM:\t'%.*s'\nEXPAND:\t%s\n=====\n",
			(int)tok->hdoc.lim.len,
			tok->hdoc.lim.s, yesno[tok->hdoc.expand]);
	}
	else if (tok->tok == VAR)
	{
		printf("=====\nVAR:\t$\nNAME:\t'%.*s'\nQTYPE:\t%d\n=====\n",
			(int)tok->s.len, tok->var.s.s, tok->var.qtype);
	}
	else
		printf("wtf, error\n");
	free_lbuild(tok);
}

static int	*parse_line(char *s, int *err, int *exc)
{
	t_list	*tmp;

	tmp = parse_quotes(s, err, exc);
	tmp = parse_pars(tmp, err, exc);
	parse_op(&tmp, err, exc);
	parse_hdoc(&tmp, err, exc);
	parse_var(&tmp, err, exc);
	if (tmp == NULL && g_sig == 0)
		return (NULL);
	//parse *, >> > <
	//a partir de heredoc il faut free les strings du reste avec free_lbuild
	//><>> peuvent prendre des mix de $ et txt
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
	int	*tree;

	tree = parse_line(s, err, exc);
	//check ctrl c
	//gestion erreur (check null)
	//exec
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	int		err;
	int		exit_code;

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
	check_err(err);
	rl_clear_history();
	return (exit_code);
}
