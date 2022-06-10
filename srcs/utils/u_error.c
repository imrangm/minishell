/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/07 16:00:14 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	err_print(int error, t_data *data)
{
	perror("Error");
	data->last_exit_status = error;
}

void	err_free_parent(int **pipes, int *pids, int nchild)
{
	free_2d_int(pipes, nchild);
	safe_free(pids);
	perror("Error");
}

void	err_free_process(int **pipes, char ***args, int nchild)
{
	free_2d_int(pipes, nchild);
	free_3d(args, nchild);
	perror("Error");
}

void	err_kill_process(t_pipe **p)
{
	p[0]->data->last_exit_status = 1;
	perror("Error");
	kill(getpid(), 9);
}
