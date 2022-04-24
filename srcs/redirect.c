/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:40:16 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/23 10:42:08 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child_here(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = 0;
	j = 0;
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	first_child_infile(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = 0;
	j = 0;
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	last_child_append(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = nchild - 1;
	j = 0;
	while (j < nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close(pipes[i - 1][0]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	last_child_outfile(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = nchild - 1;
	j = 0;
	while (j < nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close(pipes[i - 1][0]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}