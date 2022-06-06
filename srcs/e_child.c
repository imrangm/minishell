/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/27 14:08:12 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child(char **arg, int **pipes, t_pipe **p)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < p[0]->nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	redir_in(p, i);
	if (!redir_out(p, i))
		dup2(pipes[i][1], STDOUT_FILENO);
	close(pipes[i][1]);
	if (exec_cmd_child(arg, p[0]->data) == -1)
		err_print(127, p[0]->data);
}

void	mid_child(int *i, char **arg, int **pipes, t_pipe **p)
{
	int	j;
	int	n;

	j = 0;
	n = p[0]->nchild;
	while (j < n - 1)
	{
		if (*i - 1 != j)
			close(pipes[j][0]);
		if (*i != j)
			close(pipes[j][1]);
		j++;
	}
	if (!redir_in(p, (*i)))
		dup2(pipes[(*i) - 1][0], STDIN_FILENO);
	if (!redir_out(p, (*i)))
		dup2(pipes[*i][1], STDOUT_FILENO);
	close(pipes[(*i) - 1][0]);
	close(pipes[*i][1]);
	if (exec_cmd_child(arg, p[0]->data) == -1)
		err_print(127, p[0]->data);
}

void	last_child(char **arg, int **pipes, t_pipe **p)
{
	int	i;
	int	j;

	i = p[0]->nchild - 1;
	j = 0;
	while (j < p[0]->nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	if (!redir_in(p, i))
		dup2(pipes[i - 1][0], STDIN_FILENO);
	redir_out(p, i);
	close(pipes[i - 1][0]);
	if (exec_cmd_child(arg, p[0]->data) == -1)
		err_print(127, p[0]->data);
}
