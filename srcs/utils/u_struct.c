/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/02 11:04:46 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct_pipe(t_pipe **p, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free(p[i]);
		i++;
	}
	ft_free(p);
}

void	ps_free(int **pipes, int *pids, t_pipe **p)
{
	int	i;

	i = 0;
	while (i < p[0]->nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	ft_free(pids);
	free_struct_pipe(p, p[0]->nchild);
}

void	rd_free(int *fd, char **arg)
{
	ft_free(fd);
	ft_free_2d(arg);
}

void	free_data(t_data *data)
{
	ft_free(data->pwd);
	ft_free_2d(data->envp);
}
