/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 16:17:35 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Child processes created to run the programs
*/
void	first_child(int nchild, char **arg, int **pipes, t_pipe **p)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	redir_in(p, i);
	if (!redir_out(p, i))
		dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	if (exec_cmd(arg, p[0]->data) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	mid_child(int *i, int nchild, char **arg, int **pipes, t_pipe **p)
{
	int	j;

	j = 0;
	while (j < nchild - 1)
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
	if (exec_cmd(arg, p[0]->data) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	last_child(int nchild, char **arg, int **pipes, t_pipe **p)
{
	int	i;
	int	j;

	i = nchild - 1;
	j = 0;
	while (j < nchild - 1)
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
	if (exec_cmd(arg, p[0]->data) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}