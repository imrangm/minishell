/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/18 07:16:41 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipe(t_pipecmd *pcmd)
{
	int	i;

	i = 0;
	while (i < pcmd->nchild)
	{
		ft_free(pcmd->p[i]);
		i++;
	}
	ft_free(pcmd->p);
}

void	ps_free(int **pipes, int *pids, t_pipecmd *pcmd)
{
	int	i;

	i = 0;
	while (i < pcmd->nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	ft_free(pids);
	free_pipe(pcmd);
}

void	free_data(t_data *data)
{
	ft_free(data->pwd);
	ft_free_2d(data->envp);
}
