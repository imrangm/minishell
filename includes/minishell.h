/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/09 18:59:44 by nmadi            ###   ########.fr       */
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

typedef struct s_data
{
	int		last_exit_status;
	int		shlvl;
	char	*pwd;
	char	*old_pwd;
	char	**envp;
}	t_data;

typedef struct s_redirs
{
	char	*infile;
	char	*heredoc;
	char	*outfile;
	char	*append;
	char	lastin;
	char	lastout;
}	t_redirs;

typedef struct s_pipe
{
	char		*fcmd;
	int			nchild;
	t_redirs	rd;
	t_data		*data;
}	t_pipe;

# define DQUOTE 34
# define SQUOTE 39

//* I/O redirection
void	file_parent(int *pid, t_data *data);
void	create_file(char *line, t_redirs *rd, t_data *data);
void	init_rd(t_redirs *rd);
void	empty_file(char *file);
void	close_fds(int *fd);
void	process(char *line, t_redirs *rd);
void	execute_rd(char *line, t_data *data);
void	handle_pp(char *line, t_data *data);

//* Execution
char	*find_exec(char *prg, char	**paths);
char	*get_cmd_path(char **args, t_data *data);
void	master_execute(char *line, t_data *data);
char	*read_line(char *lim);
char	**ft_split_path(char *s, char c);
char	**split_rd(char *str);
int		count_redir(char *input);
int		char_is_separator(char c, char *charset);

//* Piping
void	here_pipe(t_pipe *p);
void	first_child(char **arg, int **pipes, t_pipe **p);
void	mid_child(int *i, char **arg, int **pipes, t_pipe **p);
void	last_child(char **arg, int **pipes, t_pipe **p);
void	parent(char ***arg, int **pipes, int *pids, t_pipe **p);
void	create_process(char ***arg, int **pipes, t_pipe **p);
int		redir_in(t_pipe **p, int i);
int		redir_out(t_pipe **p, int i);
int		count_pipes(char *line);
void	pipes(t_pipe **p);

//* Error and free
void	err_print(int error, t_data *data);
void	err_free_parent(int **pipes, int *pids, int nchild);
void	no_err_free_parent(int **pipes, int *pids);
void	err_kill_process(t_pipe **p);
void	err_free_process(int **pipes, char ***args, int nchild);
void	safe_free(void *ptr);
void	free_2d_int(int **arr, int nchild);
void	free_2d(char **arr);
void	free_3d(char ***arr, int nchild);
char	**chars_split(char *str, char *charset);
void	here_ops(char *line);
void	append(char *line);
char	**ft_split_path(char *s, char c);
char	*expand_env(char *str);
int		exec_cmd_child(char **args, t_data *data);
void	exec_cmd_parent(char **args, t_data *data);
int		is_parent_function(char **args);
void	free_struct(t_redirs *rd);

//* Parsing
int		pc_valid(char *str, t_data *data);
int		pc_mode(char *str, char mode);
int		pc_quotes(char *str);
int		pc_chars(char *str);
int		pc_redirs(char *str);
int		pc_end(char *line);
int		pc_pipe(char *line);
int		pc_redir(char *line);
int		pc_export(char *str);
char	*line_unquote(char *input);
char	*cmd_copy(char *input);
int		check_space(char *str);
int		word_count(char *input);
char	*first_word(char *input);
char	*rem_words(char *input);
char	*find_cmd(char *input);
char	*set_cmd(char *s1, char *s2);

//* Signals
void	handle_signals(int signum);
int		in_minishell_var(int is_true);

//* Builtins
int		b_env(char **envp, int export_mode);
int		b_pwd(t_data *data);
void	b_export(char **args, t_data *data);
void	b_unset(char **args, t_data *data);
int		b_cd(char **args, t_data *data);
void	b_exit(char **args, t_data *data);
int		b_echo(char **args, t_data *data);

//* Environment Variables
char	*get_env_value(char *str, char **envp);
int		env_exists(char *var_name, char **envp);
char	**add_env(char *var_name, char *value, char **envp);
void	delete_env(char *var_name, char **envp);
void	modify_env(char *var_name, char *value, char **envp);
char	**append_env(char *var_name, char *value, char **envp);
char	**clone_env(char **envp, int extra_slot);
char	*get_export_value_side(char *str, int lhs);
char	*expand_envs(char *str, char **envp);
char	**init_envp(char **envp);

//* Misc (Organize)
int		set_quote_mode(char c, int *quote);
char	**split_pp(char const *s, char c);
// void		set_shlvl(int *shlvl, int value, char **envp);

void	free_struct_rd(t_redirs *rd);
void	free_struct_ps(t_pipe **p, int nchild);
void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p);
void	rd_free(int *fd, char **arg, t_redirs *rd);
char	*ft_strjoin_and_free(char *s1, char const *s2);

//* cd utils
char	*join_paths(char *cwd, char *np);
int		invalid_args_count(char **args, t_data *data);
int		root_relative_chdir(char *new_path);
int		relative_chdir(char *new_path, char *pwd);
int		full_chdir(char *new_path);

char	**smart_split(char *str);
#endif