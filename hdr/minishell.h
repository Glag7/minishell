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
# include <unistd.h>
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

// builtins
//	cd.c
int		builtin_cd(int argc, char **argv, char **envp);
//	env.c
int		builtin_env(int argc, char **argv, char **envp);
//	pwd.c
int		builtin_pwd(int argc, char **argv, char **envp);
//	unset.c
int		builtin_unset(int argc, char **argv, char ***envp);
//	export.c
int		builtin_export(int argc, char **argv, char ***envp);
//	exit.c
int		builtin_exit(int argc, char **argv, char **envp);
//	echo.c
int		builtin_echo(int argc, char **argv, char **envp);
//	builtin_utils.c
char	*ft_strappend(char *src1, char *src2, char mode);
char	**get_var(char **envp, char *var);
int		replace_var(char **envp, char *new, char *old_name);
int		remove_var(char ***envp, char *var);

// output.c
void	ft_perror(char	*s);
//

#endif
