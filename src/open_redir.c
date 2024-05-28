/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:41:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/28 18:12:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_out(t_redir *red, int *inout)
{
	int	err;

	if (red->redir == OUT)
	{
		inout[0] = open(red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (inout[0] == -1)
		{
			err = errno;
			ft_perror3("minishell: ", red->filename[0], ": ");
			ft_perror3(strerror(err), "\n", "");
			return (1);
		}
	}
	else if (red->redir == APP)
	{
		inout[0] = open(red->filename[0], O_WRONLY | O_CREAT, 0644);
		if (inout[0] == -1)
		{
			err = errno;
			ft_perror3("minishell: ", red->filename[0], ": ");
			ft_perror3(strerror(err), "\n", "");
			return (1);
		}
	}
	return (0);
}

static int	open_redir_type(t_redir *red, int *inout)
{
	int	err;

	if (red->filename[0] == NULL || red->filename[1] != NULL)
	{
		ft_perror("minishell: ambiguous redirect\n");
		return (1);
	}
	if (red->redir == IN || red->redir == HDOC)
	{
		inout[0] = open(red->filename[0], O_RDONLY);
		if (inout[0] == -1)
		{
			err = errno;
			ft_perror3("minishell: ", red->filename[0], ": ");
			ft_perror3(strerror(err), "\n", "");
			return (1);
		}
	}
	else
		return (open_out(red, inout));
	return (0);
}

int	open_redir(t_mini *mini, t_list *redir, int *inout)
{
	t_redir	*red;

	inout[0] = -1;
	inout[1] = -1;
	while (redir)
	{
		red = (t_redir *)redir->content;
		if ((red->redir & OUT) && inout[1] != -1)
			close(inout[1]);
		else if (!(red->redir & OUT) && inout[0] != -1)
			close(inout[0]);
		if (open_redir_type(red, inout))
		{
			if (inout[0] != -1)
				close(inout[0]);
			if (inout[1] != -1)
				close(inout[1]);
			mini->exc = 1;
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
