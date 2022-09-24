/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:40:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:05:42 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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

typedef struct s_glb
{
	int	*last_exit_status;
	int	child_pid;
}	t_glb;

t_glb	g_glb;
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
	t_redirs	rd;
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
	int				exp;
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
	t_data	*data;
}	t_execcmd;

typedef struct s_redircmd
{
	int			type;
	char		*fcmd;
	t_redirs	rd;
	t_data		*data;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_pipe	**p;
	int		nchild;
	t_data	*data;
}	t_pipecmd;

//* Parsing
t_charlist	*scan_input(char *input);
t_toklist	*tokenize(t_charlist *src);
void		init_token(t_token *tokens);
void		init_toklist(t_toklist *tokens);
int			count_tokens(t_token *tok);
int			has_more_tokens(t_toklist *toks);
int			look_ahead(t_toklist *toks);
char		*current_token(t_toklist *toks);
void		next_token(t_toklist *toks);
int			process_redirection(t_node **left, t_node **right, char *current);
int			expansion(t_toklist *toklist, t_token *token, t_data *data);
int			expander(t_toklist *toks, t_token *token, t_exp *exp, t_data *data);
int			check_exp(char *str);

//* AST
t_node		*parse(t_data *data);
t_node		*parse_pipeline(t_toklist *toks);
t_node		*parse_command(t_toklist *toks);
t_node		*parse_redirection(t_toklist *toks, char *id);
t_node		*parse_io(t_node *node, t_toklist *toks);
t_cmd		*process_command(t_node *root, int count, t_data *data);
t_redirs	get_redir(t_node *rd);
void		add_redir(t_redirs *rd, char *op, char *fname);
t_node		*pair_node(t_node *left, t_node *right, char *id);
t_node		*error_node(char *msg);
t_execcmd	*exec_cmd(char *fcmd, t_data *data);
t_redircmd	*redir_cmd(char *fcmd, t_redirs *rd, t_data *data);
t_pipecmd	*pipe_cmd(t_pipe **p, int nchild, t_data *data);
void		execute(t_cmd *cmd);
void		process_io(t_node **n, t_toklist *toks);
void		u_check_io(t_node **n, t_toklist *toks, int *io);

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

//* Simple Command
void		scmd(t_execcmd *exec);
char		*find_exec(char *prg, char	**paths);
char		*get_cmd_path(char **args, t_data *data);

//* Redirection
void		redirs(t_redircmd *redir);
void		process_redirs(int *fd, t_redircmd *redir);
void		init_rd(t_redirs *rd);
int			empty_file(char *file);
int			fd_in(t_redirs *rd);
int			fd_out(t_redirs *rd);
void		close_fds(int *fd);
void		add_redir(t_redirs *rd, char *op, char *fname);
t_redirs	get_redir(t_node *rd);
void		free_redirs_pipe(t_pipecmd *pcmd);
void		exit_pipe_rd(int *pids, int **pipes, t_pipecmd *pcmd);
void		exit_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd);
void		exec_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd);

//* Pipes
void		pipes(t_pipecmd *pcmd);
void		ps_free_all(int **pipes, t_pipecmd *pcmd);
int			count_pipes(char *line);
int			redir_in(t_pipe **p, int i);
int			redir_out(t_pipe **p, int i);
void		first_child(int *pids, int **pipes, t_pipecmd *pcmd);
void		mid_child(int *i, int *pids, int **pipes, t_pipecmd *pcmd);
void		last_child(int *pids, int **pipes, t_pipecmd *pcmd);
void		create_process(int **pipes, t_pipecmd *pcmd);
void		file_error(t_pipecmd *pcmd);
void		file_error_mid(int **pipes, t_pipecmd *pcmd, int i);
void		close_pipes_first(int **pipes, t_pipecmd *pcmd, int i);
void		close_pipes_mid(int **pipes, t_pipecmd *pcmd, int i);
void		close_pipes_last(int **pipes, t_pipecmd *pcmd, int i);
void		cmd_pipe(char **args, t_data *data);

//* Command Execution
int			is_builtin(char **args);
void		builtin(char **args, t_cmd *cmd, t_data *data);
void		cmd(char **args, t_data *data);

//* Free
void		free_pipe(t_pipecmd *pcmd);
void		ps_free(int **pipes, int *pids, t_pipecmd *pcmd);
void		free_data(t_data *data);
void		free_and_exit(char **args, t_cmd *cmd, t_data *data);
void		free_expansion(t_exp *exp);
void		free_expansion_all(t_exp *exp);

//* Preliminary Checkers
int			pc_redirs(char *str);
int			pc_export(char **args);
int			pc_valid(char *str, t_data *data);
int			pc_start(char *line, t_data *data);

//* Parsing Extractors
char		**smart_split(char *str);
char		**pe_split_path(char *s, char c);
char		**strip_quotes(char **elements, int element_count);

//* Builtins
int			b_pwd(t_data *data);
int			b_cd(char **args, t_data *data);
void		b_exit(char **args, t_cmd *cmd, t_data *data);
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
void		handle_signal_and_heredoc(t_pipecmd *pcmd, int *pids, int i);
void		handle_termsig(int wstatus, t_data *data);

//* Misc
void		free_redirs(t_redircmd *redir);
char		*read_line(char *lim);
void		ft_readline(char *lim);
int			check_io(char *prev, char *current);
int			check_error(t_node *node, t_data *data);
char		op_type(char *op);
int			check_space(char *str);
char		*ft_strjoin_and_free(char *s1, char const *s2);
char		*read_pipe(char *line);
char		*join_env_var_and_value(char *var_name, char *value);
char		*trim_line(char *line);
int			end_pipe(char *line);
char		*read_pipe(char *line);
int			start_param(char *str);
int			end_param(char *str);
char		*quote_removal(char *str);
void		ps_fork_error(int *pids, int **pipes, t_pipecmd *pcmd);


#endif