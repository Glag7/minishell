/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:14:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/22 18:55:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_tok	get_next_word(t_mini *mini, t_list **lst)
{
	t_list	*curr;
	t_tok	*tok;
	t_tok	ret;

	curr = *lst;
	ret = (t_tok){0, .type = 0};//get len
	//cpy
	while (curr)
	{
		tok = ((t_tok *)curr);
		if ((tok->tok == HDOC || tok->tok == REDIR) && ret.tok == UNDEF)
			return (*tok);
		if ((tok->tok == HDOC || tok->tok == REDIR))
			return (ret);//epic malloc first
	}
}

int	split_words(t_mini *mini, t_list **lst)
{
	t_list	*words;
	t_list	*curr;
	t_tok	tok;

	curr = *lst;
	words = NULL;
	while (curr)
	{
		tok = get_next_word(mini, &curr);
		if (tok.tok == REDIR || tok.tok == HDOC)
			//add it
		else if (tok->var.qtype)
		{
			tok.s = tok->var.s;
			//add it
		}
		else
			continue ;
		//add undef
	}
	return (0);
}
