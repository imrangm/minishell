/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/04 20:13:14 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/all_includes.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	int	in_main_shell;
} t_data;

typedef struct s_redirs
{
	char	*infile;
	char	*outfile;
	char	*append;
	char	*heredoc;
} t_redirs;

typedef struct s_pipe
{
	char		*fcmd;
	char		**lr; //line reference
	t_redirs	rd;
	void		*prev;
	void		*next;
} t_pipe;

# define DQUOTE 34
# define SQUOTE 39

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
int		count_pipes(char *line);
void	pipes(char *line, t_pipe **p);
void	execute(char *line);
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);
char	**chars_split(char *str, char *charset);
void	here_ops(char *line, t_redirs *rd);
void	file_parent(int *pid);
void	file(char *line, t_redirs *rd);
char	**ft_split_path(char *s, char c);
int		find_sym(char **line, char *sym);
char	*cmd_copy(char *input);
void	process(char *line, t_redirs *rd);
void 	split_rd(char *line);
void	split_pipe(char *line);

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