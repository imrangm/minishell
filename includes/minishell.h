/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/14 18:17:20 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/all_includes.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>

typedef struct s_data
{
	int		last_exit_status;
	int		shlvl;
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

typedef struct s_fork
{
	int		nchild;
	char	**arg;
	int		**pipes;
	char	**envp;
}	t_fork;

typedef struct s_pipe
{
	char		*fcmd;
	t_redirs	rd;
	t_fork		fr;
	t_data		*data;
}	t_pipe;

# define DQUOTE 34
# define SQUOTE 39

//* I/O redirection
void	file_parent(int *pid, t_data *data);
void	create_file(char *line, t_redirs *rd, t_data *data);
void	reset_rd(t_redirs *rd);
int		multi_cmd_redir(char *input);
void	split_multi_cmd_redir(char **input, t_redirs *rd, t_data *data);

//* Execution
char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char*cmd, t_data *data);
int		count_pipes(char *line);
void	pipes(char *line, t_pipe **p);
void	master_execute(char *line, t_data *data);
char	**ft_split_chars(char *str, char *charset);
char	*read_line(char *lim);
char	**ft_split_path(char *s, char c);
char	**ft_split_rd(char *str);
char	*redir_cpy(char *input);
char	*rm_redir(char *input);
int		count_redir(char *input);
int		char_is_separator(char c, char *charset);
int		check_space(char *str);
int		word_count(char *input);
char	*first_word(char *input);
char	*rem_words(char *input);
char	*find_cmd(char *input);
char	*cmd_unquote(char *input);

//* Struct
char	*cmd_copy(char *input);
void	process(char *line, t_redirs *rd);
void	split_rd(char *line, t_data *data);
void	split_pipe(char *line, t_data *data);

//* Pipe
void	here_pipe(t_pipe *p);
void	first_child(int nchild, char **arg, int **pipes, t_pipe **p);
void	mid_child(int *i, int nchild, char **arg, int **pipes, t_pipe **p);
void	last_child(int nchild, char **arg, int **pipes, t_pipe **p);
void	parent(int nchild, int **pipes, int *pids);
void	create_process(int nchild, char ***arg, int **pipes, t_pipe **p);
int		redir_in(t_pipe **p, int i);
int		redir_out(t_pipe **p, int i);

//* Error and free
void	err_print(int error, t_data *data);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);
char	**chars_split(char *str, char *charset);
void	here_ops(char *line);
void	append(char *line);
char	**ft_split_path(char *s, char c);
char	*expand_env(char *str);
int		exec_cmd_child(char **args, t_data *data);
char	**exec_cmd_parent(char **args, t_data *data);
int		is_parent_function(char *str);
int		p_env_error(char *str);

//* Parsing
int		preliminary_check(char *str, t_data *data);
int		p_contains_unclosed_quotes(char *str);
int		p_is_empty_input(char *str);
int		p_contains_illegal_special_chars(char *str);
int		p_contains_invalid_redirs(char *str);
int		p_check_end(char *line);
int		p_check_pipe(char *line);
int		p_check_redir(char *line);
char	*cmd_unquote(char *input);

//* Signals
void	handle_signals(int signum);
int		in_minishell_var(int is_true);

//* Builtins
int		b_env(char **envp, int export_mode);
int		b_pwd(void);
int		b_cd(char *new_path);
int		b_echo(char **args, t_data *data);

//* Environment Variables
char		*get_env_value(char *str, char **envp);
int			env_exists(char *var_name, char **envp);
char		**add_env(char *var_name, char *value, char **envp);
void		unset_env(char *var_name, char **envp);
void		modify_env(char *var_name, char *value, char **envp);
char		**append_env(char *var_name, char *value, char **envp);
char		**clone_env(char **envp, int extra_slot);
char		*get_export_value_side(char *str, int lhs);
char		**expand_envs(char **str, char **envp);
long long	m_atoi(const char *str);
int			are_digits(char *str);
char		*get_export_value_side(char *str, int lhs);
// void		set_shlvl(int *shlvl, int value, char **envp);

#endif