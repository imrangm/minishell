/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/09 16:08:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_pipe(char **arg, int *pids, int **pipes, t_pipe **p)
{
	t_data		*data;

	data = p[0]->data;
	ps_free(pipes, pids, p);
	ft_free(data->line);
	free_and_exit(arg, data);
}

static void	exec_pipe(char **arg, int *pids, int **pipes, t_pipe **p)
{
	if (is_parent_function(arg))
		exit_pipe(arg, pids, pipes, p);
	if (is_builtin(arg))
	{
		exec_builtin(arg, p[0]->data);
		exit_pipe(arg, pids, pipes, p);
	}
	else
	{
		exec_cmd(arg, p[0]->data);
		exit_pipe(arg, pids, pipes, p);
	}
}

void	first_child(int *pids, int **pipes, t_pipe **p)
{
	int			i;
	char		**arg;
	int			ret;

	i = 0;
	arg = smart_split(p[0]->fcmd);
	close_pipes_first(pipes, p, i);
	ret = redir_in(p, i);
	if (ret == -1)
	{
		file_error(p);
		close(pipes[i][1]);
		exit_pipe(arg, pids, pipes, p);
	}
	ret = redir_out(p, i);
	if (ret == -1)
	{
		file_error(p);
		close(pipes[i][1]);
		exit_pipe(arg, pids, pipes, p);
	}
	if (!ret)
		dup2(pipes[i][1], STDOUT_FILENO);
	close(pipes[i][1]);
	exec_pipe(arg, pids, pipes, p);
}

void	mid_child(int *i, int *pids, int **pipes, t_pipe **p)
{
	char	**arg;
	int		ret;

	arg = smart_split(p[*i]->fcmd);
	close_pipes_mid(pipes, p, *i);
	ret = redir_in(p, (*i));
	if (ret == -1)
	{
		file_error_mid(pipes, p, *i);
		exit_pipe(arg, pids, pipes, p);
	}
	if (!ret)
		dup2(pipes[(*i) - 1][0], STDIN_FILENO);
	ret = redir_out(p, (*i));
	if (ret == -1)
	{
		file_error_mid(pipes, p, *i);
		exit_pipe(arg, pids, pipes, p);
	}
	if (!ret)
		dup2(pipes[*i][1], STDOUT_FILENO);
	close(pipes[(*i) - 1][0]);
	close(pipes[*i][1]);
	exec_pipe(arg, pids, pipes, p);
}

void	last_child(int *pids, int **pipes, t_pipe **p)
{
	int		i;
	char	**arg;
	int		ret;

	i = p[0]->nchild - 1;
	arg = smart_split(p[i]->fcmd);
	close_pipes_last(pipes, p, i);
	ret = redir_in(p, i);
	if (ret == -1)
	{
		file_error(p);
		close(pipes[i - 1][0]);
		exit_pipe(arg, pids, pipes, p);
	}
	if (!ret)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	ret = redir_out(p, i);
	if (ret == -1)
	{
		file_error(p);
		close(pipes[i - 1][0]);
		exit_pipe(arg, pids, pipes, p);
	}
	close(pipes[i - 1][0]);
	exec_pipe(arg, pids, pipes, p);
}
