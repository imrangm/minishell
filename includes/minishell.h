/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 08:04:55 by imustafa         ###   ########.fr       */
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
	int	in_main_shell;
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
}	t_pipe;

# define DQUOTE 34
# define SQUOTE 39

//* Checks
int		check_end(char *line);
int		check_pipe(char *line);
int		check_redir(char *line);

//* I/O redirection
void	file_parent(int *pid);
void	file(char *line, t_redirs *rd);

//* Execution
char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
int		count_pipes(char *line);
void	pipes(char *line, t_pipe **p);
void	execute(char *line);
char	**ft_split_chars(char *str, char *charset);
char	*read_line(char *lim);
char	**ft_split_path(char *s, char c);
char	**ft_split_rd(char *str);
char	*redir_cpy(char *input);
char	*rm_redir(char *input);
int		count_redir(char *input);
int		char_is_separator(char c, char *charset);
int		check_space(char *str);

//* Struct
char	*cmd_copy(char *input);
void	process(char *line, t_redirs *rd);
void	split_rd(char *line);
void	split_pipe(char *line);

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
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);
void	ft_free_arg(char **arr);

//* Parsing
int		preliminary_check(char *str);
int		p_contains_unclosed_quotes(char *str);
int		p_first_element(char *str);
int		p_illegal_chars(char *str);
int		p_contains_invalid_redirs(char *str);

//* Signals
void	handle_signals(int signum);
int		in_minishell_var(int is_true);

#endif