/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 16:58:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	debug(void *tok_)
{
	t_tok		*tok;
	t_quote		slice;
	static char	*yesno[2] = {"no", "yes"};
	static char	*type[4] = {"in", "out", "???", "app"};

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
		printf("=====\nHDOC:\t<<\nLIM:\t'%.*s'\nLEN:\t%zu\nEXP:\t%s\n=====\n",
			(int)tok->hdoc.lim.len,
			tok->hdoc.lim.s, tok->hdoc.lim.len, yesno[tok->hdoc.expand]);
	else if (tok->tok == VAR)
		printf("=====\nVAR:\t$\nNAME:\t'%.*s'\nLEN:\t%zu\nQTYPE:\t%d\n=====\n",
			(int)tok->s.len, tok->var.s.s, tok->var.s.len, tok->var.qtype);
	else if (tok->tok == WDCARD)
		printf("=====\nWDCARD:\t*\n=====\n");
	else if (tok->tok == REDIR)
		printf("=====\nREDIR\nTYPE:\t%s\n=====\n",
			type[tok->redir]);
	else
		printf("wtf, error\n");
	free_lbuild(tok);
}

static t_list	*parse_line(char *s, int *err, int *exc)
{
	t_list	*tmp;

	tmp = parse_quotes(s, err, exc);
	parse_op(&tmp, err, exc);
	parse_pars(&tmp, err, exc);
	parse_hdoc(&tmp, err, exc);
	parse_var(&tmp, err, exc);
	parse_wdcard(&tmp, err, exc);
	parse_redir(&tmp, err, exc);
	if (*err || (tmp == NULL && g_sig == 0))
		return (NULL);
	if (g_sig == SIGINT)
	{
		*exc = 128 + SIGINT;
		ft_lstclear(&tmp, &free_lbuild);
		return (NULL);
	}
	return (tmp);//signaux
}

static void	exec_line(char *s, int *err, int *exc, t_envp *senvp)
{
	t_list	*toexec;

	if (s == NULL)
		*err = ERR_BYEBYE;
	if (s == NULL || *s == 0)
	{
		free(s);
		return ;
	}
	add_history(s);
	toexec = parse_line(s, err, exc);
	if (toexec == NULL)
		return ;
	execline(toexec, err, exc, senvp);//is faut free s
	ft_lstclear(&toexec, &free_lexec);
	//signaux
}//todo t_minishell avec le prompt, la liste, les hdocs

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_envp	senvp;
	int		err;
	int		exit_code;

	(void) argc;
	(void) argv;
	err = dup_envp(&envp);
	senvp = (t_envp) {envp, 1, 1};
	exit_code = 0;
	//if (err == 0)
	//sig handler
	while (err == 0)
	{
		s = readline("coquillage de petite taille > ");
		exec_line(s, &err, &exit_code, &senvp);
		free(s);
	}
	check_err(err);
	ft_freearr(envp);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (exit_code);
}
