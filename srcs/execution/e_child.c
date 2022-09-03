/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 07:52:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/03 11:17:41 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_child(int *pids, int **pipes, t_pipe **p)
{
	int			i;
	int			j;
	char		**arg;
	t_data		*data;

	i = 0;
	j = 0;
	arg = ft_split(p[0]->fcmd, ' ');
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
	if (is_parent_function(arg))
		exit (0);
	if (is_builtin(arg))
	{
		exec_builtin(p[0]->fcmd, arg, p[0]->data);
		data = p[0]->data;
		ps_free(pipes, pids, p);
		ft_free(data->line);
		free_and_exit(arg, data);
	}
	else
	{
		exec_cmd_child(arg, p[0]->data);
		err_print(127, p[0]->data);
	}
}

void	mid_child(int *i, int *pids, int **pipes, t_pipe **p)
{
	int		j;
	int		n;
	char	**arg;
	t_data	*data;

	j = 0;
	n = p[0]->nchild;
	arg = ft_split(p[*i]->fcmd, ' ');
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
	if (is_parent_function(arg))
	{
		ps_free(pipes, pids, p);
		exit (0);
	}
	if (is_builtin(arg))
	{
		exec_builtin(p[*i]->fcmd, arg, p[0]->data);
		data = p[0]->data;
		ps_free(pipes, pids, p);
		free_and_exit(arg, data);
	}
	if (exec_cmd_child(arg, p[0]->data) == -1)
		err_print(127, p[0]->data);
}

void	last_child(int *pids, int **pipes, t_pipe **p)
{
	int		i;
	int		j;
	char	**arg;
	t_data	*data;

	i = p[0]->nchild - 1;
	j = 0;
	arg = ft_split(p[i]->fcmd, ' ');
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
	if (is_parent_function(arg))
	{
		ps_free(pipes, pids, p);
		exit (0);
	}
	if (is_builtin(arg))
	{
		exec_builtin(p[i]->fcmd, arg, p[0]->data);
		data = p[0]->data;
		ps_free(pipes, pids, p);
		free_and_exit(arg, data);
	}
	if (exec_cmd_child(arg, p[0]->data) == -1)
		err_print(127, p[0]->data);
}
