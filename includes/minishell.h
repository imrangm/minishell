/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/17 17:17:41 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../libs/readline/include/readline/readline.h"
# include "../libs/readline/include/readline/history.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

/* TOKEN TYPE */
# define SPACES 0
# define WORD 1
# define PIPE 2
# define REDIR 3
# define SQUOTE 4
# define DQUOTE 5

/* COMMAND TYPE */
# define SCMD 6
# define RCMD 7
# define PCMD 8

/* SYMBOLS */
# define LINE '|'
# define GREAT '>'
# define LESS '<'
# define DGREAT '+'
# define DLESS '-'

int	g_child_pid;

typedef struct s_exp
{
	int		start;
	int		end;
	char	*param;
	char	*value;
}	t_exp;
typedef struct s_node
{
	int				type;
	char			*id;
	char			*value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;	

typedef struct s_data
{
	int		last_exit_status;
	int		error;
	char	*line;
	int		shlvl;
	char	*pwd;
	char	**envp;
	t_node	*root;
}	t_data;

typedef struct s_redirs
{
	char	*infile;
	char	*heredoc;
	char	*outfile;
	char	*append;
	int		lastin;
	int		lastout;
}	t_redirs;

typedef struct s_pipe
{
	char		*fcmd;
	int			nchild;
	t_redirs	rd;
	t_data		*data;
}	t_pipe;

typedef struct s_char
{
	char	c;
	int		t;
}	t_char;

typedef struct s_charlist
{
	t_char	**chars;
	int		len;
	int		pos;
}	t_charlist;

typedef struct s_token
{
	int				type;
	char			*value;
	int				space;
	struct s_token	*next;
}	t_token;

typedef struct s_toklist
{
	t_token		*first;
	t_token		*current;
	int			count;
	int			id;
}	t_toklist;

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*fcmd;
}	t_execcmd;

typedef struct s_redircmd
{
	int			type;
	char		*fcmd;
	t_redirs	rd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_pipe	**pipes;
}	t_pipecmd;

//* Parsing
t_charlist	*scan_input(char *input);
t_toklist	*tokenize(t_charlist *src);
int			count_tokens(t_token *tok);
int			has_more_tokens(t_toklist *toks);
int			look_ahead(t_toklist *toks);
char		*current_token(t_toklist *toks);
void		next_token(t_toklist *toks);
int			process_redirection(t_node **left, t_node **right, char *current);

//* AST
t_node		*parse(t_data *data);
t_node		*parse_pipeline(t_toklist *toks);
t_node		*parse_command(t_toklist *toks);
t_node		*parse_redirection(t_toklist *toks);
t_node		*parse_io(t_node *node, t_toklist *toks, char *id);
void		add_redir(t_redirs *rd, char *op, char *fname);
t_cmd		*process_command(t_node *root, int count, t_data *data);
t_redirs	get_redir(t_node *rd);

//* Expansion
void		expansion(t_token *token, t_data *data);
void		expander(t_token *token, t_exp *exp, t_data *data);

//* Nodes
t_node		*pair_node(t_node *left, t_node *right, char *id);
t_node		*error_node(char *msg);

//* Parsing to Execution
t_execcmd	*exe_cmd(char *fcmd);
t_redircmd	*redir_cmd(char *fcmd, t_redirs *rd);
t_pipecmd	*pipe_cmd(t_pipe **p, int nchild);
void		execute(t_cmd *cmd, t_data *data);

//* Free Memory
void		free_chars(t_charlist *src);
void		free_tokens(t_token *tok);
void		free_node(t_node *node);
void		free_nodes(t_node *root);
void		free_pair(t_node *left, t_node *right);

//* Parser Tests
void		print_chars(t_charlist	*scan);
void		print_tokens(t_token *token);
void		print_ast(t_node *node, size_t spaces);

//* Utility
void		init_token(t_token *tokens);
void		init_toklist(t_toklist *tokens);
int			check_io(char *prev, char *current);
int			check_error(t_node *node, t_data *data);
char		op_type(char *op);

//* Simple Command
void		scmd(char *line, t_data *data);
char		*find_exec(char *prg, char	**paths);
char		*get_cmd_path(char **args, t_data *data);

//* Redirection
void		redirs(char *line, t_redirs *rd, t_data *data);
void		process_redirs(int *fd, char *line, t_redirs *rd, t_data *data);
void		init_rd(t_redirs *rd);
void		empty_file(char *file);
int			fd_in(t_redirs *rd);
int			fd_out(t_redirs *rd);
void		close_fds(int *fd);

//* Pipes
void		pipes(t_pipe **p);
void		ps_free_all(int **pipes, t_pipe **p);
int			count_pipes(char *line);
int			redir_in(t_pipe **p, int i);
int			redir_out(t_pipe **p, int i);
void		first_child(int *pids, int **pipes, t_pipe **p);
void		mid_child(int *i, int *pids, int **pipes, t_pipe **p);
void		last_child(int *pids, int **pipes, t_pipe **p);
void		create_process(int **pipes, t_pipe **p);
void		file_error(t_pipe **p);
void		file_error_mid(int **pipes, t_pipe **p, int i);
void		close_pipes_first(int **pipes, t_pipe **p, int i);
void		close_pipes_mid(int **pipes, t_pipe **p, int i);
void		close_pipes_last(int **pipes, t_pipe **p, int i);

//* Command Execution
int			is_parent_function(char **args);
int			is_builtin(char **args);
void		exec_builtin(char **args, t_data *data);
void		exec_cmd(char **args, t_data *data);
void		free_and_exit(char **args, t_data *data);

//* Free
void		free_struct_pipe(t_pipe **p, int nchild);
void		ps_free(int **pipes, int *pids, t_pipe **p);
void		rd_free(int *fd, char **arg);
void		free_data(t_data *data);

//* Preliminary Checkers
int			pc_pipe(char *line);
int			pc_redirs(char *str);
int			pc_export(char **args);
int			pc_valid(char *str, t_data *data);

//* Parsing Extractors
char		**smart_split(char *str);
char		**pe_split_path(char *s, char c);

//* Builtins
int			b_pwd(t_data *data);
int			b_cd(char **args, t_data *data);
void		b_exit(char **args, t_data *data);
int			b_echo(char **args, t_data *data);
void		b_unset(char **args, t_data *data);
void		b_export(char **args, t_data *data);
int			b_env(char **envp, int export_mode);

//* Environment Variables
void		init_envp(char **envp, t_data *data);
char		*get_env_value(char *str, t_data *data);
int			env_exists(char *var_name, t_data *data);
void		delete_env(char *var_name, t_data *data);
char		**clone_env(char **envp, int extra_slot);
char		*get_export_value_side(char *str, int lhs);
void		modify_env(char *var_name, char *value, t_data *data);
void		append_env(char *var_name, char *value, t_data *data);

//* cd utils
int			cd_absolute(char *new_path);
int			cd_relative(char *new_path, char *pwd);
int			cd_special(void);

//* Signals
void		set_signalset(int sigmode);
void		quit_signal_handler(int signum);

//* Misc
char		*read_line(char *lim);
void		ft_readline(char *lim);
int			check_space(char *str);
char		*ft_strjoin_and_free(char *s1, char const *s2);
void		line_update(char **line);
char		*join_env_var_and_value(char *var_name, char *value);
char		*trim_line(char *line);
void		end_pipe(char **line);

#endif