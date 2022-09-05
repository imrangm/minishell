/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/05 05:45:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(char *line)
{
	int	i;
	int	p;
	int	q;

	i = 0;
	p = 0;
	q = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]) && !q)
			q = line[i];
		else if (line[i] == q)
			q = 0;
		else if (line[i] == '|')
			p++;
		i++;
	}
	return (p);
}

static void	ps_free_main(t_pipe **p)
{
	free_data(p[0]->data);
	free_nodes(p[0]->data->root);
	p[0]->data->last_exit_status = 1;
}

static void	ps_free_pipes(int **pipes, t_pipe **p)
{
	ft_free(pipes);
	ps_free_main(p);
}

void	ps_free_all(int **pipes, t_pipe **p)
{
	int		i;
	int		nchild;

	i = 0;
	nchild = p[0]->nchild;
	while (i < nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ps_free_pipes(pipes, p);
}

int	**create_pipes(t_pipe **p)
{
	int		**pipes;
	int		i;

	i = 0;
	pipes = malloc(sizeof(int *) * (p[0]->nchild));
	if (!pipes)
	{
		ps_free_main(p);
		perror("Malloc failed");
	}
	while (i < p[0]->nchild)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ps_free_pipes(pipes, p);
			perror("Malloc failed");
		}
		i++;
	}
	return (pipes);
}

void	pipes(t_pipe **p)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = create_pipes(p);
	while (i < p[0]->nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ps_free_all(pipes, p);
			perror("Pipe failed");
		}
		i++;
	}
	create_process(pipes, p);
}
