/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:51:22 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 16:31:12 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redirs_pipe(t_pipecmd *pcmd)
{
	t_data	*data;

	data = pcmd->data;
	ft_free(pcmd);
	free_data(data);
	free_nodes(data->root);
	exit(data->last_exit_status);
}

void	exit_pipe_rd(int *pids, int **pipes, t_pipecmd *pcmd)
{
	ps_free(pipes, pids, pcmd);
	ft_free(pcmd->data->line);
	free_redirs_pipe(pcmd);
}

void	exit_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd)
{
	ps_free(pipes, pids, pcmd);
	ft_free(pcmd->data->line);
	free_and_exit(arg, (t_cmd *) pcmd, pcmd->data);
}

void	exec_pipe(char **arg, int *pids, int **pipes, t_pipecmd *pcmd)
{
	if (arg && is_builtin(arg))
	{
		builtin(arg, (t_cmd *) pcmd, pcmd->data);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	else if (arg)
	{
		cmd_pipe(arg, pcmd->data);
		exit_pipe(arg, pids, pipes, pcmd);
	}
	else
	{
		exit_pipe_rd(pids, pipes, pcmd);
	}
}
