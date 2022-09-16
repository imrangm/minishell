/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/16 13:40:56 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc(char **args, t_data *data)
{
	int	f;

	f = open("tmp", O_RDONLY, 0);
	if (f == -1)
	{
		data->last_exit_status = 1;
		free_and_exit(args, data);
	}
	dup2(f, STDIN_FILENO);
	close(f);
	unlink("tmp");
}

static void	child(int *fd, char *line, t_redirs *rd, t_data *data)
{
	char	**args;

	args = smart_split(line);
	if (rd->heredoc)
		heredoc(args, data);
	else
		dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (is_builtin(args))
		exec_builtin(args, data);
	else
		exec_cmd(args, data);
	close_fds(fd);
	free_and_exit(args, data);
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

void	process_redirs(int *fd, char *line, t_redirs *rd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		data->last_exit_status = 140;
		ft_putstr_fd("Error: Could not create child process\n", 2);
		return ;
	}
	if (pid == 0)
		child(fd, line, rd, data);
	else
		parent(&pid, data);
}

void	redirs(char *line, t_redirs *rd, t_data *data)
{
	int		fd[2];

	fd[0] = fd_in(rd);
	fd[1] = fd_out(rd);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("File error");
		data->last_exit_status = 1;
	}
	else
	{
		process_redirs(fd, line, rd, data);
		close_fds(fd);
	}
}
