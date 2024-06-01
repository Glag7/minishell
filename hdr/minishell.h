/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:55:37 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/01 17:03:18 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ----- INCLUDES ----- */

# include "libft.h"
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>

////////////////////////

/* COMMON */

# define ERR_BYEBYE	-1
# define ERR_AINTNOWAY	3
# define ERR_SHUTUP	111

# define MSG_MALLOC	"minishell: malloc: epic fail\n"

void	ft_perror(char	*s);
void	ft_perror3(char	*s1, char *s2, char *s3);
void	check_err(int err, int forked);

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
# define HDOC_REDIR 4

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
		t_quote			var;
		bool			type;
	};
}	t_tok;

t_list	*parse_quotes(char *s, int *err, int *exc);
void	parse_op(t_list **lst, int *err, int *exc);
int		check_op(t_list *lst);
void	parse_pars(t_list **lst, int *err, int *exc);
void	parse_hdoc(t_list **lst, int *err, int *exc);
int		search_lim(t_list *lst, t_tok *tok, size_t i, t_hdoc *hdoc);
void	parse_var(t_list **lst, int *err, int *exc);
void	parse_wdcard(t_list **lst, int *err, int *exc);
void	parse_redir(t_list **lst, int *err, int *exc);
int		check_redir(t_list *lst);
void	remove_dup_par(t_list **lst);

////////////////////////////////////////////

/* ----- BUILTINS ----- */

// Structure used to hide PWD and OLDPWD
typedef struct s_envp
{
	char	**envp;
	bool	show_pwd;
	bool	show_oldpwd;
}	t_envp;

// Warning macro
# define WARNING_SHELL_INIT	"shell-init: error retrieving current directory: \
getcwd(): cannot access parent directories: no such file or directory\n"

// Prototypes
int		builtin_cd(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_env(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_pwd(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_unset(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_export(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_exit(size_t argc, char **argv, t_envp *envp_status, int *fds);
int		builtin_echo(size_t argc, char **argv, t_envp *envp_status, int *fds);
bool	update_cd_envp(t_envp *envp_status);
int		export_to_envp(char **argv, t_envp *envp_status);
int		update_envp(char **new_envp, char **argv, t_envp *envp_status,
			size_t len);
int		copy_envp(char **new_envp, char **old_envp, size_t len);
int		check_existence(char *var, char **envp);
int		check_syntax(char *var);
int		export_only(t_envp envp_status, int fd);
char	*ft_strappend(char *src1, char *src2, char mode);
char	**get_var(char **envp, char *var);
size_t	len_until_char(char *str, char c);
int		replace_var(char **envp, char *new, char *old_name);
void	remove_var(char **envp, char *var, void (*del)(void *));
ssize_t	ft_print(char *builtin, int fd, char *str, size_t len);

////////////////////////////////////////////

/* EXEC */

# define READ 0
# define WRITE 1

typedef struct s_mini
{
	char	*prompt;
	char	*hprompt;
	char	*s;
	t_list	*exec;
	t_list	*hdocs;
	t_list	*pids;
	t_envp	envp;
	int		exc;
	int		err;
	int		forked;
	int		oldpipe[2];
	int		newpipe[2];
}	t_mini;

typedef struct s_cmd
{
	char	**cmd;
	t_list	*redir;
	bool	fork;
	bool	builtin;
}	t_cmd;

typedef struct s_redir
{
	int		redir;
	char	**filename;
}	t_redir;

void	wrap_builtin(t_mini *mini, char **argv, int *inout);
void	execline(t_mini *mini, t_list *exec);
void	exec_cmd(t_mini *mini, t_list **exec);
int		parse_cmd(t_mini *mini, t_list *exec, t_cmd *cmd);
int		split_words(t_mini *mini, t_list **lst);
int		get_fnames(t_mini *mini, t_str **fnames);
int		add_word_str(t_mini *mini, t_list **lst, t_list *curr);
int		get_redir(t_mini *mini, t_list *toparse,
			const t_tok space, t_cmd *cmd);
int		exp_wdcard(t_mini *mini, t_list **lst, t_str *fnames);
int		add_wdname(t_list **files, t_list *curr, t_str name);
int		get_cmd(t_mini *mini, t_cmd *cmd, t_list *toparse);
int		fill_heredocs(t_list *lst, t_mini *mini);
int		build_redirs(t_mini *mini, t_cmd *cmd, t_list *lst);
int		open_redir(t_mini *mini, t_list *redir, int *inout);
int		fill_file(int fd, t_str lim, t_mini *mini);
int		get_path(t_mini *mini, char **cmd, char **dst);
void	get_path_err(t_mini *mini, int err, char *name);
void	waitall(t_mini *mini);
void	do_builtin(t_mini *mini, t_cmd *cmd);
void	do_cmd(t_mini *mini, t_cmd *cmd);
int		parse_wdcard_again(t_list **lst, int *err, int *exc);

int		hdoc_replace(t_mini *mini, t_hdoc hdoc);
t_str	varchr(t_str s, char **envp, t_mini *mini);

void	close_pipes(t_mini *mini);
int		update_pipes(t_mini *mini, t_list *exec);

bool	next_is_pipe(t_list *exec);
t_list	*find_next_op(t_list *exec);
t_list	*find_next_op_type(t_list *exec, bool type);

//////////////////////////////////////////////

void	init_mini(t_mini *mini, int argc, char **argv, char **envp);
int		dup_envp(char ***envp_ptr);
char	*increment_shlvl(char *old_shlvl);
int		check_numeric(char *str);

//free
t_list	*free_wdcard(t_list *lst);
void	free_lbuild(void *tok_);
void	free_lexec(void *tok_);
void	free_lredir(void *tok_);
void	free_fnames(t_str *fnames);

/* SIGNAL */

# define SIG_IGNORE 0
# define SIG_INTER 1
# define SIG_HDOC 2
# define SIG_EXEC 4
# define SIG_BUILTIN 5

void	handle_builtin(int sig);
void	handle_hdoc(int sig);
void	handle_inter(int sig);
void	sig_mode(int mode);
///////////////////////////////////////////

//wrap
void	wrap_unlink(void *name);
void	wrap_freearr(void *envp);

#endif
