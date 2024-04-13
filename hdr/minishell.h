/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/13 14:00:30 by glag             ###   ########.fr       */
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
# define ERR_PARSE -1

//parsing
# define QUOTE 1
# define DQUOTE 2

typedef struct s_quote
{
	int	qtype;
	t_str	str;
}	t_quote;

t_list	*parse_quotes(char *s, int *err);
//

//output
# define MSG_QUOTE "minishell: syntax error: open quote\n"

void	ft_perror(char	*s);
//

#endif
