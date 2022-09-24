/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:45:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 15:01:57 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_signal(int pid)
{
	g_glb.child_pid = pid;
	signal(SIGQUIT, &quit_signal_handler);
}

static void	ps_fork_error(int *pids, int **pipes, t_pipecmd *pcmd)
{
	ps_free(pipes, pids, pcmd);
	pcmd->data->last_exit_status = 140;
	ft_putstr_fd("Error: Could not create child process\n", 2);
}

static void	parent(int *pids, int **pipes, t_pipecmd *pcmd)
{
	int	i;
	int	wstatus;
	int	signal_caught;
	int	code;

	i = 0;
	wstatus = 0;
	while (i < pcmd->nchild - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pcmd->nchild)
		waitpid(pids[i++], &wstatus, 0);
	signal_caught = WTERMSIG(wstatus);
	if (signal_caught == 2) // SIGINT
		pcmd->data->last_exit_status = 130;
	else if (signal_caught == 3) // SIGQUIT
		pcmd->data->last_exit_status = 131;
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			pcmd->data->last_exit_status = code;
	}
	ps_free(pipes, pids, pcmd);
}

static void	child_process(int *pids, int **pipes, t_pipecmd *pcmd)
{
	int	i;

	i = 0;
	while (i < pcmd->nchild)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ps_fork_error(pids, pipes, pcmd);
			return ;
		}
		if (pids[i] == 0)
		{
			if (i == 0)
				first_child(pids, pipes, pcmd);
			if (i < pcmd->nchild - 1)
				mid_child(&i, pids, pipes, pcmd);
			if (i == pcmd->nchild - 1)
				last_child(pids, pipes, pcmd);
		}
		else
		{
			if (pcmd->p[i]->rd.heredoc)
				waitpid(pids[i], NULL, 0);
			handle_signal(pids[i]);
		}
		i++;
	}
}

void	create_process(int **pipes, t_pipecmd *pcmd)
{
	int	*pids;

	pids = malloc (sizeof(int) * pcmd->nchild);
	if (!pids)
	{
		ps_free_all(pipes, pcmd);
		perror("Malloc failed");
	}
	child_process(pids, pipes, pcmd);
	parent(pids, pipes, pcmd);
}
