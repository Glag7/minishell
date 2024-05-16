/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:53:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/16 19:13:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

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
	sig_mode(SIG_IGNORE);
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
	mini->hdocs = NULL;
	fill_heredocs(mini->exec, mini);
	if (mini->err == 0)
		execline(mini, mini->exec);
	if (mini->forked == 0)
		ft_lstclear(&mini->hdocs, &wrap_unlink);
	else
		ft_lstclear(&mini->hdocs, NULL);
	ft_lstclear(&mini->exec, &free_lbuild);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	init_mini(&mini, argc, argv, envp);
	while (mini.err == 0)
	{
		sig_mode(SIG_INTER);
		mini.s = readline(mini.prompt);
		exec_line(&mini);
		free(mini.s);
		if (mini.forked && mini.err == 0)
			mini.err = ERR_BYEBYE;
	}
	check_err(mini.err, mini.forked);
	wrap_freearr(mini.envp.envp);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (mini.exc);
}
