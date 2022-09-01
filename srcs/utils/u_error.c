/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/31 10:36:48 by imustafa         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	ft_free(pids);
	perror("Error");
}

void	err_free_process(int **pipes, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	perror("Error");
}

void	err_kill_process(t_pipe **p)
{
	p[0]->data->last_exit_status = 1;
	perror("Error");
	exit(1);
}
