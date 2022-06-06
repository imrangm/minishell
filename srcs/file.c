/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/06 19:20:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_child(int *fd, char **arg, t_redirs *rd, t_data *data)
{
	int	f;

	f = 0;
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
	if (exec_cmd_child(arg, data) == -1)
	{
		rd_free(fd, arg, rd);
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

void	file_process(int *fd, char *cmd, t_redirs *rd, t_data *data)
{
	int		pid[2];
	char	**arg;

	arg = ft_split(cmd, ' ');
	safe_free(cmd);
	// if (!ft_strncmp(arg[0], "env", ft_strlen(arg[0])))
	// {
	// 	b_env(data->envp, 0);
	// 	free_2d(arg);
	// 	return ;
	// }
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
	{
		file_child(fd, arg, rd, data);
	}
	else
	{
		file_parent(pid, data);
		rd_free(fd, arg, rd);
	}
}

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;

	line = strdup("");
	final = line;
	write(1, "> ", 2);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (!ft_strncmp (line, lim, ft_strlen(lim)))
				break ;
			final = ft_strjoin(final, line);
			free(line);
			line = strdup("");
			write(1, "> ", 2);
		}
	}
	free (line);
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
	}
	if (rd->infile && rd->lastin == 'i')
		fd[0] = open(rd->infile, O_RDONLY | O_CLOEXEC);
	if (rd->outfile && rd->lastout == 'o')
		fd[1] = open(rd->outfile, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
	if (rd->append && rd->lastout == 'a')
		fd[1] = open(rd->append, O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0644);
	if (fd[0] == -1 || fd[1] == -1)
		perror("File error");
	else
		file_process(fd, line, rd, data);
}
