/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/03 14:25:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_child(int *fd, char *line, t_redirs *rd, t_data *data)
{
	int		f;
	char	**args;

	f = 0;
	args = ft_split(line, ' ');
	if (rd->heredoc && rd->lastin == 'h')
	{
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
	else
		dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (is_builtin(args))
	{
		exec_builtin(line, args, data);
		close(fd[0]);
		close(fd[1]);
		ft_free(fd);
		free_and_exit(args, data);
	}
	if (exec_cmd_child(args, data) == -1)
	{
		rd_free(fd, args);
		err_print(127, data);
	}
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
	{
		file_child(fd, line, rd, data);
	}
	else
	{
		file_parent(pid, data);
	}
}

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;

	line = ft_strdup("");
	final = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		line = ft_strjoin_and_free(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (!ft_strncmp (line, lim, ft_strlen(lim)))
				break ;
			final = ft_strjoin_and_free(final, line);
			ft_free(line);
			line = strdup("");
			write(1, "> ", 2);
		}
	}
	ft_free(line);
	return (final);
}

void	create_file(char *line, t_redirs *rd, t_data *data)
{
	int		*fd;
	char	*text;

	fd = (int *) malloc (sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 1;
	if (rd->heredoc && rd->lastin == 'h')
	{
		fd[0] = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		text = read_line(rd->heredoc);
		write(fd[0], text, strlen(text));
		close(fd[0]);
		ft_free(text);
	}
	if (rd->infile && rd->lastin == 'i')
		fd[0] = open(rd->infile, O_RDONLY | O_CLOEXEC);
	if (rd->outfile && rd->lastout == 'o')
		fd[1] = open(rd->outfile, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
	if (rd->append && rd->lastout == 'a')
		fd[1] = open(rd->append, O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0644);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("File error");
		data->last_exit_status = 1;
	}
	else
		file_process(fd, line, rd, data);
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	ft_free(fd);
}
