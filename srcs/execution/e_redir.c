/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 18:04:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child(int *fd, t_redircmd *redir)
{
	char	**args;

	if (redir->fcmd)
		args = smart_split(redir->fcmd);
	else
		args = NULL;
	if (redir->rd.heredoc)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (redir->fcmd)
	{
		if (is_builtin(args))
			builtin(args, (t_cmd *) redir, redir->data);
		else
			cmd(args, redir->data);
	}
	close_fds(fd);
	ft_free(redir->data->line);
	if (args)
		free_and_exit(args, (t_cmd *) redir, redir->data);
	else
		free_redirs(redir);
}

static void	parent(int *pid, t_data *data)
{
	int	wstatus;
	int	signal_caught;
	int	code;

	g_glb.child_pid = *pid;
	signal(SIGQUIT, &quit_signal_handler);
	waitpid(*pid, &wstatus, 0);
	signal_caught = WTERMSIG(wstatus);
	if (signal_caught == 2)
		data->last_exit_status = 130;
	else if (signal_caught == 3)
		data->last_exit_status = 131;
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			data->last_exit_status = code;
		else
			data->last_exit_status = 0;
	}
}

void	process_redirs(int *fd, t_redircmd *redir)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		redir->data->last_exit_status = 140;
		ft_putstr_fd("Error: Could not create child process\n", 2);
		return ;
	}
	if (pid == 0)
		child(fd, redir);
	else
		parent(&pid, redir->data);
}

void	redirs(t_redircmd *redir)
{
	int		fd[2];

	fd[0] = fd_in(&redir->rd);
	fd[1] = fd_out(&redir->rd);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("File error");
		redir->data->last_exit_status = 1;
	}
	else
	{
		process_redirs(fd, redir);
		close_fds(fd);
	}
}
