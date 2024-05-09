/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:43 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/09 15:18:37 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_mini *mini)
{
	if (mini->oldpipe[0] != -1)
		close(mini->oldpipe[0]);
	if (mini->oldpipe[1] != -1)
		close(mini->oldpipe[1]);
	if (mini->newpipe[0] != -1)
		close(mini->newpipe[0]);
	if (mini->newpipe[1] != -1)
		close(mini->newpipe[1]);
	mini->newpipe[0] = -1;
	mini->newpipe[1] = -1;
	mini->oldpipe[0] = -1;
	mini->oldpipe[1] = -1;
}

int	update_pipes(t_mini *mini, t_list *exec)
{
	if (mini->oldpipe[0] != -1)
		close(mini->oldpipe[0]);
	if (mini->oldpipe[1] != -1)
		close(mini->oldpipe[1]);
	mini->oldpipe[0] = mini->newpipe[0];
	mini->oldpipe[1] = mini->newpipe[1];
	mini->newpipe[0] = -1;
	mini->newpipe[1] = -1;
	while (exec && ((t_tok *)exec->content)->tok != PIPE
		&& ((t_tok *)exec->content)->tok != OP)
		exec = exec->next;
	if (!exec || ((t_tok *)exec->content)->tok != PIPE
		|| pipe(mini->newpipe) != -1)
		return (0);
	ft_perror3("minishell: pipe: ", strerror(errno), "\n");
	mini->exc = 2;
	mini->err = ERR_SHUTUP;
	if (mini->oldpipe[0] != -1)
		close(mini->oldpipe[0]);
	if (mini->oldpipe[1] != -1)
		close(mini->oldpipe[1]);
	mini->oldpipe[0] = -1;
	mini->oldpipe[1] = -1;
	return (1);
}
