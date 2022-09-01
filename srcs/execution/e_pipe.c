/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/31 10:37:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_pipes(t_pipe **p)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * (p[0]->nchild));
	if (!pipes)
		perror("Malloc failed");
	while (i < p[0]->nchild)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			perror("Malloc failed");
		i++;
	}
	i = 0;
	while (i < p[0]->nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
			err_free_process(pipes, p[0]->nchild);
		i++;
	}
	create_process(pipes, p);
}

void	pipes(t_pipe **p)
{
	// int		i;
	// char	***arg;

	// i = 0;
	// arg = malloc (sizeof(char **) * p[0]->nchild);
	// if (!arg)
	// 	perror("Malloc failed");
	// while (i < p[0]->nchild)
	// {
	// 	arg[i] = ft_split(p[i]->fcmd, ' ');
	// 	i++;
	// }
	create_pipes(p);
}
