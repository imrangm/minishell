/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/20 19:53:23 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/all_includes.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	pipes(char *line);
void	execute(char *line);
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);

#endif