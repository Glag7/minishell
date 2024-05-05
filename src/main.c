/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 17:22:03 by glaguyon         ###   ########.fr       */
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
	if (*err || tmp == NULL)
		return (NULL);
	return (tmp);
}

static void	exec_line(t_mini *mini)
{
	if (g_sig == SIGINT)
	{
		mini->exc = 128 + g_sig;
		g_sig = 0;
	}
	if (mini->s == NULL)
		mini->err = ERR_BYEBYE;
	if (mini->s == NULL || *mini->s == 0)
		return ;
	add_history(mini->s);
	mini->exec = parse_line(mini->s, &mini->err, &mini->exc);
	if (mini->exec == NULL)
		return ;
	execline(mini);
	ft_lstclear(&mini->exec, &free_lexec);
	//ft_lstclear(&mini->exec, &debug);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	init_mini(&mini, argc, argv, envp);
	while (mini.err == 0)
	{
		mini.s = readline(mini.prompt);
		exec_line(&mini);
		free(mini.s);
	}
	check_err(mini.err, mini.forked);
	ft_freearr(mini.envp.envp);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (mini.exc);
}
