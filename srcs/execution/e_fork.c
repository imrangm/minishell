/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:45:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/16 13:46:06 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_signal(int pid)
{
	g_child_pid = pid;
	signal(SIGQUIT, &quit_signal_handler);
}

static void	parent(int *pids, int **pipes, t_pipe **p)
{
	int	i;
	int	wstatus;
	int	code;

	i = 0;
	wstatus = 0;
	while (i < p[0]->nchild - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < p[0]->nchild)
		waitpid(pids[i++], &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			p[0]->data->last_exit_status = code;
	}
	if (access("tmp", F_OK))
		unlink("tmp");
	ps_free(pipes, pids, p);
}

static void	child_process(int *pids, int **pipes, t_pipe **p, int i)
{
	while (i < p[0]->nchild)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ps_free(pipes, pids, p);
			p[0]->data->last_exit_status = 140;
			ft_putstr_fd("Error: Could not create child process\n", 2);
			return ;
		}
		if (pids[i] == 0)
		{
			if (i == 0)
				first_child(pids, pipes, p);
			if (i < p[0]->nchild - 1)
				mid_child(&i, pids, pipes, p);
			if (i == p[0]->nchild - 1)
				last_child(pids, pipes, p);
		}
		else
			handle_signal(pids[i]);
		i++;
	}
}

void	create_process(int **pipes, t_pipe **p)
{
	int	*pids;

	pids = malloc (sizeof(int) * p[0]->nchild);
	if (!pids)
	{
		ps_free_all(pipes, p);
		perror("Malloc failed");
	}
	child_process(pids, pipes, p, 0);
	parent(pids, pipes, p);
}
