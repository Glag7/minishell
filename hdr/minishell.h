/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/24 19:58:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ----- INCLUDES ----- */

# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ----- STRUCTURES & MACROS ----- */

//errors
# define ERR_AINTNOWAY	3
//

//parsing
# define QUOTE	1
# define DQUOTE	2

typedef struct s_quote
{
	int		qtype;
	t_str	str;
}	t_quote;

# define AND	0
# define OR	1
# define OPEN	0
# define CLOSE	1

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

typedef struct s_var
{
	int	qtype;
	t_str	s;
}	t_var;

typedef struct s_redir
{
	int	tok;
	int	type;
	union
	{
		t_str	s;
		t_var	var;
		t_list	*wdcard;
		t_list	*any;
	};
}	t_redir;

typedef struct s_hdoc
{
	bool	expand;
	t_str	lim;
}	t_hdoc;

typedef struct s_tok
{
	int	tok;
	union
	{
		t_quote			quote;
		t_str			s;
		struct s_redir	redir;
		struct s_hdoc	hdoc;
		struct s_var	var;
		bool			type;
		t_list			*wdcard;
	};
}	t_tok;

/* ----- PROTOTYPES & MACROS ----- */

t_list	*parse_quotes(char *s, int *err, int *exc);
t_list	*parse_pars(t_list *lst, int *err, int *exc);
int		check_pars(t_list *pars, ssize_t plevel);
void	parse_op(t_list **lst, int *err, int *exc);
int	check_op(t_list *lst);
void	parse_hdoc(t_list **lst, int *err, int *exc);
int	search_lim(t_list *lst, t_tok *tok, size_t i, t_hdoc *hdoc);
void	parse_var(t_list **lst, int *err, int *exc);
//

//output
# define MSG_QUOTE	"minishell: syntax error: open quote\n"
# define MSG_PAR	"minishell: syntax error: bad parenthesis\n"
# define MSG_OP		"minishell: syntax error: bad operator\n"
# define MSG_HDOC	"minishell: syntax error: bad heredoc\n"

# define MSG_MALLOC	"minishell: malloc: epic fail\n"

void	ft_perror(char	*s);
void	check_err(int err);
//

//free
void	free_lbuild(void *tok_);
void	free_wdcard(void *tok_);
//

// builtins
int		builtin_cd(int argc, char **argv, char **envp);
int		builtin_env(int argc, char **argv, char **envp);
int		builtin_pwd(int argc, char **argv, char **envp);
int		builtin_unset(int argc, char **argv, char **envp);
int		builtin_export(int argc, char **argv, char ***envp);
int		builtin_exit(int argc, char **argv, char **envp);
int		builtin_echo(int argc, char **argv, char **envp);
char	export_to_envp(char **argv, char ***envp);
char	check_existence(char *var, char **envp);
char	check_syntax(char *var);
char	export_only(char **envp);
char	*ft_strappend(char *src1, char *src2, char mode);
char	**get_var(char **envp, char *var);
char	strgreater(void *ptr1, void *ptr2);
size_t	len_until_char(char *str, char c);
int		replace_var(char **envp, char *new, char *old_name);
void		remove_var(char **envp, char *var);
//

#endif
