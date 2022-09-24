/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:19:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:10:45 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_signal(int pid)
{
	g_glb.child_pid = pid;
	signal(SIGQUIT, &quit_signal_handler);
}

void	ps_fork_error(int *pids, int **pipes, t_pipecmd *pcmd)
{
	ps_free(pipes, pids, pcmd);
	pcmd->data->last_exit_status = 140;
	ft_putstr_fd("Error: Could not create child process\n", 2);
}

void	handle_signal_and_heredoc(t_pipecmd *pcmd, int *pids, int i)
{
	if (pcmd->p[i]->rd.heredoc)
		waitpid(pids[i], NULL, 0);
	handle_signal(pids[i]);
}

void	handle_termsig(int wstatus, t_data *data)
{
	int	signal_caught;

	signal_caught = WTERMSIG(wstatus);
	if (signal_caught == 2)
		data->last_exit_status = 130;
	else if (signal_caught == 3)
		data->last_exit_status = 131;
}
