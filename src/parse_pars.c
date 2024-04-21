/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:25 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/21 19:32:31 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	*dup_txt(t_list **src, t_list **dst, int *err, int *exc)
{
	t_tok	*tok;
	t_list	*tmp;

	tok = malloc(sizeof(*tok));
	tmp = ft_lstnew(tok);
	if (tok == NULL || tmp == NULL)
	{
		free(tmp);
		free(tok);
		ft_lstclear(src, &free);
		ft_lstclear(dst, &free);
		*err = ERR_AINTNOWAY;
		*exc = 2;
		return (NULL);
	}
	tok->tok = UNDEF;
	tok->quote = *(t_quote *)((*src)->content);
	ft_lstadd_back(dst, tmp);
	return (tok);
}

static t_tok	*add_plevel(t_list **src, t_list **dst, int *err,
	ssize_t *plevel)
{
	t_tok	*tok;

	if (*plevel < 0)
	{
		ft_lstclear(src, &free);
		ft_lstclear(dst, &free);
		return (NULL);
	}
	tok = dup_txt(src, dst, err, (int *)plevel);
	return (tok);
}

static inline void	init_var(t_str *s, t_list *src, t_tok **tok)
{
	*s = ((t_quote *)src->content)->str;
	s->len = -1;
	*tok = NULL;
}

static int	add_pars(t_list **src, t_list **dst, int *err, ssize_t *plevel)
{
	t_str	s;
	t_tok	*tok;

	init_var(&s, *src, &tok);
	while (++s.len < ((t_quote *)(*src)->content)->str.len)
	{
		if (s.s[s.len] == '(' || s.s[s.len] == ')')
		{
			*plevel += (s.s[s.len] == '(') - (s.s[s.len] == ')');
			tok = add_plevel(src, dst, err, plevel);
			if (tok == NULL)
				return (1);
			*tok = (t_tok){.tok = PAR, .type = (s.s[s.len] == ')')};
		}
		else if (tok && tok->tok == UNDEF)
			tok->quote.str.len++;
		else
		{
			tok = dup_txt(src, dst, err, (int *)plevel);
			if (tok == NULL)
				return (1);
			tok->quote.str = (t_str){s.s + s.len, 1};
		}
	}
	return (0);
}

t_list	*parse_pars(t_list *lst, int *err, int *exc)
{
	t_list	*pars;
	ssize_t	plevel;

	pars = NULL;
	plevel = 0;
	while (lst)
	{
		if (((t_quote *)lst->content)->qtype && !dup_txt(&lst, &pars, err, exc))
			return (NULL);
		else if (lst && ((t_quote *)lst->content)->qtype == 0)
		{
			if (add_pars(&lst, &pars, err, &plevel))
				*exc = 2;
			if (pars == NULL || plevel < 0)
				break ;
		}
		ft_lstpop(&lst, &free, 1);
	}
	if (pars && check_pars(pars, plevel))
	{
		ft_perror(MSG_PAR);
		ft_lstclear(&pars, &free);
		*exc = 2;
	}
	return (pars);
}
