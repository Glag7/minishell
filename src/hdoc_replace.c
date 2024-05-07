/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:53:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/07 20:10:48 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_line(t_mini *mini, t_list **lst, t_str *s, int fd)
{
	t_tok	*line;

	line = malloc(sizeof(*line));
	if (line == NULL)
	{
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		ft_gnl_tstr(-1025, 0);
		return (1);
	}
	*s = ft_gnl_tstr(fd, 1024);
	*line = (t_tok){.tok = UNDEF, .quote = {.str = *s, .qtype = 0}};
	*lst = ft_lstnew(line);
	if (line->quote.str.s == NULL || *lst == NULL)
	{
		free(line->quote.str.s);
		free(line);
		free(*lst);
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		ft_gnl_tstr(-1025, 0);
		return (1);
	}
	return (0);
}

static void	replace_var_hdoc(t_list *lst, char **envp)
{
	t_tok	*tok;
	t_str	tmp;

	while (lst)
	{
		tok = (t_tok *)lst->content;
		if (tok->tok == VAR)
		{
			tmp = varchr(tok->var.s, envp);
			free(tok->var.s.s);
			*tok = (t_tok){.tok = UNDEF, .quote = {.qtype = 0, .str = tmp}};
		}
		*(t_str *)tok = (t_str)tok->quote.str;
		lst = lst->next;
	}
}

static int	add_dst(t_mini *mini, t_list *lst, int dst, char *tofree)
{
	t_list	*tmp;
	size_t	len;
	t_str	line;

	tmp = lst;
	len = 0;
	while (tmp)
	{
		len += ((t_str *)tmp->content)->len;
		tmp = tmp->next;
	}
	line = ft_lsttstr_to_tstr(&lst, len, &free, NULL);
	free(tofree);
	if (line.s == NULL)
	{
		mini->exc = 2;
		mini->err = ERR_AINTNOWAY;
		return (1);
	}
	if (write(dst, line.s, line.len) == -1)
	{
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
		ft_perror3("minishell: hdoc: ", strerror(errno), "\n");
		free(line.s);
		return (1);
	}
	free(line.s);
	return (0);
}

static int	replace_vars(t_mini *mini, int dst, int src, char **envp)
{
	t_list	*lst;
	t_str	s;

	while (1)
	{
		if (get_line(mini, &lst, &s, src))
			return (1);
		if (s.len == 0)
			break ;
		parse_var(&lst, &mini->err, &mini->exc);
		if (lst == NULL)
		{
			free(s.s);
			ft_gnl_tstr(-1025, 0);
			return (1);
		}
		replace_var_hdoc(lst, envp);
		if (add_dst(mini, lst, dst, s.s))
			return (1);
	}
	ft_gnl_tstr(-1025, 0);
	free(s.s);
	ft_lstclear(&lst, &free);
	return (0);
}

int	hdoc_replace(t_mini *mini, t_hdoc hdoc)
{
	int	fd[2];
	int	err;

	fd[0] = open(hdoc.lim.s, O_RDONLY);
	if (fd[0] == -1)
	{
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
		ft_perror3("minishell: heredoc: ", strerror(errno), "\n");
		return (1);
	}
	unlink(hdoc.lim.s);
	fd[1] = open(hdoc.lim.s, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd[1] == -1)
	{
		mini->exc = 2;
		mini->err = ERR_SHUTUP;
		close(fd[0]);
		ft_perror3("minishell: heredoc: ", strerror(errno), "\n");
		return (1);
	}
	err = replace_vars(mini, fd[1], fd[0], mini->envp.envp);
	close(fd[1]);
	close(fd[0]);
	return (err);
}
