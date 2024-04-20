/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/20 14:11:18 by glaguyon         ###   ########.fr       */
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

//parsing
# define QUOTE 1
# define DQUOTE 2

enum	e_tok
{
	UNDEF = 0;
	TXT;
	PAR;
	OP;
	PIPE;
	REDIR;
	HDOC;
	VAR;
	WDCARD;
}

typedef struct s_quote
{
	int	qtype;
	t_str	str;
}	t_quote;

# define OPEN 0
# define CLOSE 1
# define AND 0
# define OR 1
# define IN 0
# define OUT 1

typedef struct s_tok
{
	int	tok;
	bool	type;
	union
	{
		t_quote	quote;
		t_str	txt;
		t_str	lim;
		t_str	file;
	}
}

t_list	*parse_quotes(char *s, int *err, int *exc);
//

//output
# define MSG_QUOTE "minishell: syntax error: open quote\n"

void	ft_perror(char	*s);
//

#endif
