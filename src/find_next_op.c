/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:26:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/09 19:14:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	next_is_pipe(t_list *exec)
{
	ssize_t	plevel;
	t_tok	*tok;

	while (exec && ((t_tok *)exec->content)->tok != OP
		&& ((t_tok *)exec->content)->tok != PIPE)
	{
		tok = (t_tok *)exec->content;
		if (tok->tok == PAR && tok->type == CLOSE)
			return (0);
		if (tok->tok == PAR)
		{
			plevel = 0;
			while (!(plevel == 1 && tok->tok == PAR && tok->type == CLOSE))
			{
				tok = (t_tok *)exec->content;
				if (tok->tok == PAR)
					plevel += (tok->type == OPEN) - (tok->type == CLOSE);
				exec = exec->next;
			}
		}
		exec = exec->next;
	}
	if (exec && ((t_tok *)exec->content)->tok == PIPE)
		return (1);
	return (0);
}

t_list	*find_next_op(t_list *exec)
{
	ssize_t	plevel;
	t_tok	*tok;

	while (exec && ((t_tok *)exec->content)->tok != OP
		&& ((t_tok *)exec->content)->tok != PIPE)
	{
		tok = (t_tok *)exec->content;
		if (tok->tok == PAR && tok->type == CLOSE)
			return (exec);
		if (tok->tok == PAR)
		{
			plevel = 0;
			while (!(plevel == 1 && tok->tok == PAR && tok->type == CLOSE))
			{
				tok = (t_tok *)exec->content;
				if (tok->tok == PAR)
					plevel += (tok->type == OPEN) - (tok->type == CLOSE);
				exec = exec->next;
			}
		}
		exec = exec->next;
	}
	if (exec && ((t_tok *)exec->content)->tok == PIPE)
		return (exec->next);
	return (exec);
}

t_list	*find_next_op_type(t_list *exec, bool type)
{
	ssize_t	plevel;
	t_tok	*tok;

	while (exec && !(((t_tok *)exec->content)->tok == OP
			&& ((t_tok *)exec->content)->type == type))
	{
		tok = (t_tok *)exec->content;
		if (tok->tok == PAR && tok->type == CLOSE)
			return (NULL);
		if (tok->tok == PAR)
		{
			plevel = 0;
			while (!(plevel == 1 && tok->tok == PAR && tok->type == CLOSE))
			{
				tok = (t_tok *)exec->content;
				if (tok->tok == PAR)
					plevel += (tok->type == OPEN) - (tok->type == CLOSE);
				exec = exec->next;
			}
		}
		exec = exec->next;
	}
	return (exec);
}
