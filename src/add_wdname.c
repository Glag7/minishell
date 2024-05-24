/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wdname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:15:09 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/24 19:26:00 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_filename_maybe(t_list **files, t_str name,
	t_str tmps, bool any)
{
	t_list	*tmp;
	t_tok	*tok;

	if (!any && tmps.len != 0)
		return (0);
	tmps.s = ft_strdup(name.s);
	tmps.len = name.len;
	tok = malloc(sizeof(*tok));
	tmp = ft_lstnew(tok);
	if (tmps.s == NULL || tok == NULL || tmp == NULL)
	{
		free(tmps.s);
		free(tok);
		free(tmp);
		return (1);
	}
	ft_lstadd_back(files, tmp);
	*tok = (t_tok){TXT, .s = tmps};
	return (0);
}

int	check_name(t_str *tofind, t_str *name, int any)
{
	t_str	tmp;

	tmp = *name;
	if (any)
		tmp.s = ft_strnstr(name->s, tofind->s, -1);
	else
		tmp.s = ft_strnstr(name->s, tofind->s, 1);
	if (tmp.s == NULL)
		return (1);
	tmp.s += tofind->len;
	name->len -= tmp.s - name->s;
	name->s = tmp.s;
	return (0);
}

int	add_wdname(t_list **files, t_list *curr, t_str name)
{
	t_tok	*tok;
	t_str	tmp;
	bool	any;

	if (!(((t_tok *)curr->content)->tok == TXT 
		&& ((t_tok *)curr->content)->s.s[0] == '.') && name.s[0] == '.')
		return (0);
	tmp = name;
	any = 0;
	while (curr)
	{
		tok = (t_tok *)curr->content;
		if (tok->tok == WDCARD)
			any = 1;
		else if (tok->tok == TXT)
		{
			if (check_name(&tok->s, &tmp, any))
				return (0);
			any = 0;
		}
		else
			break ;
		curr = curr->next;
	}
	return (add_filename_maybe(files, name, tmp, any));
}
