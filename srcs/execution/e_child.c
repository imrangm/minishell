/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 15:54:03 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**determine_arg(int *i, t_pipecmd *pcmd)
{
	if (pcmd->p[*i]->fcmd)
		return (smart_split(pcmd->p[*i]->fcmd));
	else
		return (NULL);
}

void	first_child(int *pids, int **pipes, t_pipecmd *pcmd)
{
	char		**arg;
	int			ret;
	int			i;

	i = 0;
	arg = determine_arg(&i, pcmd);
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

	arg = determine_arg(&i, pcmd);
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
	arg = determine_arg(&i, pcmd);
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
