/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/18 07:10:08 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ps_free_main(t_pipecmd *pcmd)
{
	free_data(pcmd->data);
	free_nodes(pcmd->data->root);
	free_pipe(pcmd);
	pcmd->data->last_exit_status = 1;
	ft_free(pcmd);
}

static void	ps_free_pipes(int **pipes, t_pipecmd *pcmd)
{
	ft_free(pipes);
	ps_free_main(pcmd);
}

void	ps_free_all(int **pipes, t_pipecmd *pcmd)
{
	int		i;
	int		nchild;

	i = 0;
	nchild = pcmd->nchild;
	while (i < nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ps_free_pipes(pipes, pcmd);
}

static int	**create_pipes(t_pipecmd *pcmd)
{
	int		**pipes;
	int		i;

	i = 0;
	pipes = malloc(sizeof(int *) * (pcmd->nchild));
	if (!pipes)
	{
		ps_free_main(pcmd);
		perror("Malloc failed");
	}
	while (i < pcmd->nchild)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ps_free_pipes(pipes, pcmd);
			perror("Malloc failed");
		}
		i++;
	}
	return (pipes);
}

void	pipes(t_pipecmd *pcmd)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = create_pipes(pcmd);
	while (i < pcmd->nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ps_free_all(pipes, pcmd);
			perror("Pipe failed");
		}
		i++;
	}
	create_process(pipes, pcmd);
}
