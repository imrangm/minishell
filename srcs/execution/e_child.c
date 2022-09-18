/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/18 07:21:58 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd)
{
	ps_free(pipes, pids, pcmd);
	ft_free(pcmd->data->line);
	free_and_exit(arg, (t_cmd *) pcmd, pcmd->data);
}

static void	exec_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd)
{
	if (is_parent_function(arg))
		exit_pipe(arg, pids, pipes, pcmd);
	if (is_builtin(arg))
	{
		builtin(arg, pcmd->data);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	else
	{
		cmd(arg, pcmd->data);
		exit_pipe(arg, pids, pipes, pcmd);
	}
}

void	first_child(int *pids, int **pipes, t_pipecmd *pcmd)
{
	char		**arg;
	int			ret;
	int			i;

	i = 0;
	arg = smart_split(pcmd->p[i]->fcmd);
	close_pipes_first(pipes, pcmd, i);
	ret = redir_in(pcmd->p, i);
	if (ret == -1)
	{
		file_error(pcmd);
		close(pipes[i][1]);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	ret = redir_out(pcmd->p, i);
	if (ret == -1)
	{
		file_error(pcmd);
		close(pipes[i][1]);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	if (!ret)
		dup2(pipes[i][1], STDOUT_FILENO);
	close(pipes[i][1]);
	exec_pipe(arg, pids, pipes, pcmd);
}

void	mid_child(int *i, int *pids, int **pipes, t_pipecmd *pcmd)
{
	char	**arg;
	int		ret;

	arg = smart_split(pcmd->p[*i]->fcmd);
	close_pipes_mid(pipes, pcmd, *i);
	ret = redir_in(pcmd->p, (*i));
	if (ret == -1)
	{
		file_error_mid(pipes, pcmd, *i);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	if (!ret)
		dup2(pipes[(*i) - 1][0], STDIN_FILENO);
	ret = redir_out(pcmd->p, (*i));
	if (ret == -1)
	{
		file_error_mid(pipes, pcmd, *i);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	if (!ret)
		dup2(pipes[*i][1], STDOUT_FILENO);
	close(pipes[(*i) - 1][0]);
	close(pipes[*i][1]);
	exec_pipe(arg, pids, pipes, pcmd);
}

void	last_child(int *pids, int **pipes, t_pipecmd *pcmd)
{
	int		i;
	char	**arg;
	int		ret;

	i = pcmd->nchild - 1;
	arg = smart_split(pcmd->p[i]->fcmd);
	close_pipes_last(pipes, pcmd, i);
	ret = redir_in(pcmd->p, i);
	if (ret == -1)
	{
		file_error(pcmd);
		close(pipes[i - 1][0]);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	if (!ret)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	ret = redir_out(pcmd->p, i);
	if (ret == -1)
	{
		file_error(pcmd);
		close(pipes[i - 1][0]);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	close(pipes[i - 1][0]);
	exec_pipe(arg, pids, pipes, pcmd);
}
