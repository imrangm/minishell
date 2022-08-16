/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/16 18:28:34 by nmadi            ###   ########.fr       */
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

void	err_free_process(int **pipes, char ***args, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	i = 0;
	while (i < nchild)
	{
		ft_free_2d(args[i]);
		i++;
	}
	ft_free(args);
	perror("Error");
}

void	err_kill_process(t_pipe **p)
{
	p[0]->data->last_exit_status = 1;
	perror("Error");
	exit(1);
}
