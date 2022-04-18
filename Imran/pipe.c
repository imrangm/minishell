/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imran             #+#    #+#             */
/*   Updated: 2022/04/18 22:20:17 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

void	create_pipes(int nchild, char **av, int *fd)
{
	int		i;
	int		j;
	int		**pipes;
	char	***arg;

	i = 0;
	j = 2;
	arg = malloc (sizeof (char **) * nchild);
	while (i < nchild)
		arg[i++] = ft_split(av[j++], ' ');
	i = 0;
	pipes = malloc(sizeof(int *) * (nchild));
	while (i < nchild)
		pipes[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
			err_free_pipex(pipes, arg, 3);
		i++;
	}
	process (nchild, arg, pipes, fd);
}

int	count_pipes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '|')
			p++;
		i++;
	}
	return (p);
}

/*
** Split the line into different commands
*/
void	pipe(char *line)
{
	int		n;
	char 	*cmd;

	cmd = ft_split(line, '|');
	n = count_pipes(line) - 3;
	pipex(n, cmd);
	return (0);
}