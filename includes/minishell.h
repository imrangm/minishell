/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/04 13:42:39 by imustafa         ###   ########.fr       */
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

# define SPACES 0
# define WORD 1
# define PIPE 2
# define REDIR 3
# define SQUOTE 4
# define DQUOTE 5
# define PIPELINE "|"
# define GREAT ">"
# define DGREAT ">>"
# define LESS "<"
# define DLESS "<<"
# define UNKNWN 9

typedef struct s_node
{
	int				type;
	char			*id;
	char			*value;
	int				val;
	struct s_node	*left_node;
	struct s_node	*right_node;
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

typedef struct s_type
{
	char	c;
	int		t;
}	t_type;

typedef struct s_scan
{
	t_type	**chars;
	int		len;
	int		pos;
}	t_scan;

typedef struct s_token
{
	int				type;
	char			*value;
	int				iter;
	int				cur;
	int				count;
}	t_token;

//* Tokenizer
t_scan	*scan_input(char *input);
t_token	**tokenize(t_scan *src);
int		count_tokens(t_scan *src);

//* Parsing
int		has_more_tokens(t_token **toks);
int		look_ahead(t_token **toks);
char	*current_token(t_token **toks);
void	next_token(t_token **toks);
void	parse(char	*line, t_data *data);
t_node	*parse_pipeline(t_token **toks);
t_node	*parse_command(t_token **toks);
t_node	*parse_redirection(t_token **toks);
t_node	*parse_io(t_node *node, t_token **toks, char *id);
int		process_redirection(t_node **left, t_node **right);

//* AST
t_node	*node(t_token **toks);
t_node	*pair_node(t_node *left, t_node *right, char *id);
t_node	*error_node(char *msg);
void	expansion_node(t_node **n);
int		check_error(t_node *node, t_data *data);

//* Expansion
t_node	*attach_expansion(char *cmd, char *rem, char *value, int expansions);
t_node	*add_expansions(t_node *args);
void	expander(t_node	*raw, t_data *data);
char	*update_cmd(int start, int end, char *cmd, char *param);
void	finalize(t_node *cmd);

//* Process and Execute
void	process_tree(t_node *root, int count, t_data *data);
void	add_redir(t_redirs *rd, char *op, char *fname);
t_redirs	get_redir(t_node *rd);

//* Free Memory
void	free_chars(t_type **table, int len);
void	free_tokens(t_token **toks);
void	free_node(t_node *node);
void	free_nodes(t_node *root);
void	free_pair(t_node *left, t_node *right);

//* Parser Tests
void	print_ast(t_node *node, size_t spaces);
void	test_parse(t_token **toks);
void	test_tokenize(t_scan *source);
void	test_scan(char	*input);

//* Utility
int		check_io(char *prev, char *current);
int		is_builtin(char **args);
void	exec_builtin(char *line, char **args, t_data *data);
int		exec_sys_cmd(char **args, t_data *data);
void	exec_cmd(char **args, t_data *data);
void	exec_file_cmd(int *fd, char **args, t_data *data);
void	free_and_exit(char **args, t_data *data);

//* Redirection
void	append(char *line);
void	here_ops(char *line);
void	init_rd(t_redirs *rd);
void	empty_file(char *file);
void	process(char *line, t_redirs *rd);
void	file_parent(int *pid, t_data *data);
void	execute_rd(char *line, t_data *data);
void	create_file(char *line, t_redirs *rd, t_data *data);
int		fd_in(t_redirs *rd);
int		fd_out(t_redirs *rd);
void	close_fds(int *fd);

//* General Execution
char	*read_line(char *lim);
int		is_parent_function(char **args);
char	*find_exec(char *prg, char	**paths);
char	*get_cmd_path(char **args, t_data *data);
void	master_execute(char *line, t_data *data);
int		exec_cmd_child(char **args, t_data *data);
void	exec_cmd_parent(char *line, char **args, t_data *data);

//* Pipes
void	pipes(t_pipe **p);
void	here_pipe(t_pipe *p);
int		count_pipes(char *line);
int		redir_in(t_pipe **p, int i);
int		redir_out(t_pipe **p, int i);
void	handle_pp(char *line, t_data *data);
void	first_child(int *pids, int **pipes, t_pipe **p);
void	mid_child(int *i, int *pids, int **pipes, t_pipe **p);
void	last_child(int *pids, int **pipes, t_pipe **p);
void	create_process(int **pipes, t_pipe **p);
void	parent(int *pids, int **pipes, t_pipe **p);

//* Error and free
void	err_print(int error, t_data *data);
void	err_free_parent(int **pipes, int *pids, int nchild);
void	no_err_free_parent(int **pipes, int *pids);
void	err_kill_process(t_pipe **p);
void	err_free_process(int **pipes, int nchild);
void	free_struct_pipe(t_pipe **p, int nchild);
void	ps_free(int **pipes, int *pids, t_pipe **p);
void	rd_free(int *fd, char **arg);
void	free_data(t_data *data);

//* Parsing Checkers
int		pc_end(char *line);
int		pc_chars(char *str);
int		pc_pipe(char *line);
int		pc_quotes(char *str);
int		pc_redirs(char *str);
int		pc_redir(char *line);
int		pc_export(char **args);
int		pc_mode(char *str, char mode);
int		pc_valid(char *str, t_data *data);

//* Parsing Extractors
char	**split_rd(char *str);
char	*find_cmd(char *input);
char	*rem_words(char *input);
char	*first_word(char *input);
char	**smart_split(char *str);
char	*set_cmd(char *s1, char *s2);
char	**pe_split_path(char *s, char c);
char	**split_pp(char const *s, char c);
char	**strip_quotes(char **elements, int element_count);

//* Builtins
int		b_pwd(t_data *data);
int		b_cd(char **args, t_data *data);
void	b_exit(char *line, char **args, t_data *data);
int		b_echo(char **args, t_data *data);
void	b_unset(char **args, t_data *data);
void	b_export(char **args, t_data *data);
int		b_env(char **envp, int export_mode);

//* Environment Variables
void	init_envp(char **envp, t_data *data);
char	*get_env_value(char *str, t_data *data);
int		env_exists(char *var_name, t_data *data);
void	delete_env(char *var_name, t_data *data);
char	**clone_env(char **envp, int extra_slot);
char	*get_export_value_side(char *str, int lhs);
void	modify_env(char *var_name, char *value, t_data *data);
void	append_env(char *var_name, char *value, t_data *data);

//* cd utils
int		cd_absolute(char *new_path);
int		cd_relative(char *new_path, char *pwd);
int		cd_special(void);

//* Signals
void	set_signalset(int sigmode);
void	handle_signals_main(int signum);
void	handle_signals_else(int signum);

//* Misc
char	*expand_line(char *line, t_data *data);
char	*cmd_copy(char *input);
int		check_space(char *str);
char	*ft_strjoin_and_free(char *s1, char const *s2);
int		word_count(char *input);
int		char_is_separator(char c, char *charset);
void	line_update(char **line);
char	*join_env_var_and_value(char *var_name, char *value);

#endif