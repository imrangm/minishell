/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 02:36:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc(char **args, t_redircmd *redir)
{
	int	f;

	f = open("tmp", O_RDONLY, 0);
	if (f == -1)
	{
		redir->data->last_exit_status = 1;
		free_and_exit(args, (t_cmd *) redir, redir->data);
	}
	dup2(f, STDIN_FILENO);
	close(f);
	unlink("tmp");
}

static void	child(int *fd, t_redircmd *redir)
{
	char	**args;

	if (redir->fcmd)
		args = smart_split(redir->fcmd);
	if (redir->rd.heredoc)
		heredoc(args, redir);
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
	free_and_exit(args, (t_cmd *) redir, redir->data);
}

static void	parent(int *pid, t_data *data)
{
	int	wstatus;
	int	code;

	g_child_pid = *pid;
	signal(SIGQUIT, &quit_signal_handler);
	waitpid(*pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (!access("tmp", F_OK))
			unlink("tmp");
		if (code != 0)
			data->last_exit_status = code;
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
