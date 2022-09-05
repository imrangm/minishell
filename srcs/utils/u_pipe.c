/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 07:56:19 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/05 09:21:25 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_error(t_pipe **p)
{
	p[0]->data->last_exit_status = 1;
	ft_putstr_fd("File error\n", 2);
}

void	file_error_mid(int **pipes, t_pipe **p, int i)
{
	p[0]->data->last_exit_status = 1;
	close(pipes[i - 1][0]);
	close(pipes[i][1]);
	ft_putstr_fd("File error\n", 2);
}

void	close_pipes_first(int **pipes, t_pipe **p, int i)
{
	int	j;

	j = 0;
	while (j < p[0]->nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
}

void	close_pipes_mid(int **pipes, t_pipe **p, int i)
{
	int	j;

	j = 0;
	while (j < p[0]->nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
}

void	close_pipes_last(int **pipes, t_pipe **p, int i)
{
	int	j;

	j = 0;
	while (j < p[0]->nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
