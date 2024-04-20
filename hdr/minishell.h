/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/20 18:03:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

//errors
# define ERR_AINTNOWAY 3
//

//parsing
# define QUOTE 1
# define DQUOTE 2

typedef struct s_quote
{
	int		qtype;
	t_str	str;
}	t_quote;

# define AND 0
# define OR 1
# define OPEN 0
# define CLOSE 1

enum	e_tok
{
	UNDEF = 0,
	TXT,
	PAR,
	OP,
	PIPE,
	REDIR,
	HDOC,
	VAR,
	WDCARD
};
enum	e_redir
{
	IN = 0,
	OUT,
	APP
};

struct s_redir
{
	int	tok;
	int	type;
	union
	{
		t_str	txt;
		t_list	*wdcard;
	};
};
struct s_hdoc
{
	bool	expand;
	t_str	lim;
};

typedef struct s_tok
{
	int	tok;
	union
	{
		t_quote			quote;
		t_str			txt;
		struct s_redir	red;
		struct s_hdoc	hdoc;
		bool			type;
		t_list			*wdcard;
	};
}	t_tok;

t_list	*parse_quotes(char *s, int *err, int *exc);
t_list	*parse_pars(t_list *lst, int *err, int *exc);
//

//output
# define MSG_QUOTE "minishell: syntax error: open quote\n"
# define MSG_PAR "minishell: syntax error: bad parenthesis\n"

void	ft_perror(char	*s);
//

#endif
