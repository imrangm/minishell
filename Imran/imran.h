/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imran.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/19 11:25:22 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMRAN_H
# define IMRAN_H

# include "../central.h"
# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	pipes(char *line);
void	execute(char *line);
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids, int code);
void	err_free_pipex(int **pipes, char ***args, int error);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);

#endif