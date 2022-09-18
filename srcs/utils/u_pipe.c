/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 07:56:19 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/18 02:24:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_error(t_pipecmd *pcmd)
{
	pcmd->data->last_exit_status = 1;
	ft_putstr_fd("File error\n", 2);
}

void	file_error_mid(int **pipes, t_pipecmd *pcmd, int i)
{
	pcmd->data->last_exit_status = 1;
	close(pipes[i - 1][0]);
	close(pipes[i][1]);
	ft_putstr_fd("File error\n", 2);
}

void	close_pipes_first(int **pipes, t_pipecmd *pcmd, int i)
{
	int	j;

	j = 0;
	while (j < pcmd->nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
}

void	close_pipes_mid(int **pipes, t_pipecmd *pcmd, int i)
{
	int	j;

	j = 0;
	while (j < pcmd->nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
}

void	close_pipes_last(int **pipes, t_pipecmd *pcmd, int i)
{
	int	j;

	j = 0;
	while (j < pcmd->nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
