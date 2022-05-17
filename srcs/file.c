/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/17 08:03:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_child(int fdi, int fdo, char **arg, t_redirs *rd, t_data *data)
{
	int			f;

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
		dup2(fdi, STDIN_FILENO);
	dup2(fdo, STDOUT_FILENO);
	if (exec_cmd_child(arg, data) == -1)
	{
		close_fds(fdi, fdo);
		err_print(127, data);
	}
}

void	file_parent(int fdi, int fdo, int *pid, t_data *data)
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
		{
			close_fds(fdi, fdo);
			data->last_exit_status = code;
			exit(code);
		}
	}
}

void	file_process(int fdi, int fdo, char *cmd, t_redirs *rd, t_data *data)
{
	int		pid[2];
	char	**arg;

	arg = ft_split(cmd, ' ');
	if (!ft_strncmp(arg[0], "env", ft_strlen(arg[0])))
	{
		b_env(data->envp, 0); //? env
		ft_free_arg(arg);
		return ;
	}
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		file_child(fdi, fdo, arg, rd, data);
	else
	{
		ft_free_arg(arg);
		file_parent(fdi, fdo, pid, data);
		close_fds(fdi, fdo);
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
	int		fdi;
	int		fdo;
	char	*text;

	fdi = 0;
	fdo = 1;
	if (rd->heredoc && rd->lastin == 'h')
	{
		fdi = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		text = read_line(rd->heredoc);
		write(fdi, text, strlen(text));
		close(fdi);
	}
	if (rd->infile && rd->lastin == 'i')
		fdi = open(rd->infile, O_RDONLY | O_CLOEXEC);
	if (rd->outfile && rd->lastout == 'o')
		fdo = open(rd->outfile, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
	if (rd->append && rd->lastout == 'a')
		fdo = open(rd->append, O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0644);
	if (fdi != -1 && fdo != -1)
		file_process(fdi, fdo, line, rd, data);
	else
		perror("File error");
	reset_rd(rd);
}
