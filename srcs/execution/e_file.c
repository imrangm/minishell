/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/04 14:13:34 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_heredoc(t_redirs *rd, t_data *data)
{
	int		f;

	f = open("tmp", O_RDONLY, 0);
	if (f == -1)
	{
		data->last_exit_status = 1;
		exit(1);
	}
	dup2(f, STDIN_FILENO);
	close(f);
	unlink("tmp");
}

void	file_child(int *fd, char *line, t_redirs *rd, t_data *data)
{
	char	**args;

	args = ft_split(line, ' ');
	if (rd->heredoc)
		file_heredoc(rd, data);
	else
		dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (is_builtin(args))
	{
		exec_builtin(line, args, data);
		close_fds(fd);
		free_and_exit(args, data);
	}
	exec_file_cmd(fd, args, data);
	close_fds(fd);
	exit(data->last_exit_status);
}

void	file_parent(int *pid, t_data *data)
{
	int	wstatus;
	int	code;

	waitpid(pid[0], &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (access("tmp", F_OK))
			unlink("tmp");
		if (code != 0)
			data->last_exit_status = code;
	}
}

void	file_process(int *fd, char *line, t_redirs *rd, t_data *data)
{
	int		pid[2];

	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		file_child(fd, line, rd, data);
	else
		file_parent(pid, data);
}

void	create_file(char *line, t_redirs *rd, t_data *data)
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
		file_process(fd, line, rd, data);
	close_fds(fd);
}
