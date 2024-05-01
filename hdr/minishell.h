/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/30 18:19:54 by glaguyon         ###   ########.fr       */
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

////////////////////////

/* COMMON */

# define ERR_AINTNOWAY	3

# define MSG_MALLOC	"minishell: malloc: epic fail\n"

void	ft_perror(char	*s);
void	check_err(int err);

///////////////////////

/* ----- PARSING ----- */

//errors
# define MSG_QUOTE	"minishell: syntax error: open quote\n"
# define MSG_PAR	"minishell: syntax error: bad parenthesis\n"
# define MSG_OP		"minishell: syntax error: bad operator\n"
# define MSG_HDOC	"minishell: syntax error: bad heredoc\n"
# define MSG_REDIR	"minishell: syntax error: bad redirection\n"
//

//quotes
# define QUOTE	1
# define DQUOTE	2

typedef struct s_quote
{
	int		qtype;
	t_str	str;
}	t_quote;

//vars
typedef struct s_var
{
	int		qtype;
	t_str	s;
}	t_var;

//op
# define AND	0
# define OR	1

//par
# define OPEN	0
# define CLOSE	1

//hdoc
typedef struct s_hdoc
{
	bool	expand;
	t_str	lim;
}	t_hdoc;

//redir
# define IN 0
# define OUT 1
# define APP 3

//tokens
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
typedef struct s_tok
{
	int	tok;
	union
	{
		t_quote			quote;
		t_str			s;
		int				redir;
		struct s_hdoc	hdoc;
		struct s_var	var;
		bool			type;
	};
}	t_tok;

t_list	*parse_quotes(char *s, int *err, int *exc);
t_list	*parse_pars(t_list *lst, int *err, int *exc);
int		check_pars(t_list *pars, ssize_t plevel);
void	parse_op(t_list **lst, int *err, int *exc);
int		check_op(t_list *lst);
void	parse_hdoc(t_list **lst, int *err, int *exc);
int		search_lim(t_list *lst, t_tok *tok, size_t i, t_hdoc *hdoc);
void	parse_var(t_list **lst, int *err, int *exc);
void	parse_wdcard(t_list **lst, int *err, int *exc);
void	parse_redir(t_list **lst, int *err, int *exc);
int		check_redir(t_list *lst);

//free
void	free_lbuild(void *tok_);

////////////////////////////////////////////

/* TREES */

typedef struct s_tree
{
	void	*content;
	void	*l;
	void	*r;
}	t_tree;

t_tree	*build_tree(t_list **lbuild, int *err, int *exc);

/////////

/* BUILTINS */

typedef struct s_envp
{
	char	**envp;
	bool	show_pwd;
	bool	show_oldpwd;
}	t_envp;

// builtins
int		builtin_cd(int argc, char **argv, t_envp *envp_status);
int		builtin_env(int argc, char **argv, t_envp envp_status);
int		builtin_pwd(int argc, char **argv, char **envp);
int		builtin_unset(int argc, char **argv, t_envp *envp_status);
int		builtin_export(int argc, char **argv, t_envp *envp_status);
int		builtin_exit(int argc, char **argv, char **envp);
int		builtin_echo(int argc, char **argv, char **envp);
bool	update_cd_envp(t_envp *envp_status);
char	export_to_envp(char **argv, t_envp *envp_status);
char	check_existence(char *var, char **envp);
char	check_syntax(char *var);
char	export_only(t_envp envp_status);
char	*ft_strappend(char *src1, char *src2, char mode);
char	**get_var(char **envp, char *var);
size_t	len_until_char(char *str, char c);
int		replace_var(char **envp, char *new, char *old_name);
void	remove_var(char **envp, char *var, void (*del)(void *));
//

#endif
