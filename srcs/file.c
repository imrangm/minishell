/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 15:05:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_child(int fdi, int fdo, char **arg, t_redirs *rd)
{
	extern char	**environ;
	int			f;

	if (rd->heredoc && rd->lastin == 'h')
	{
		f = open("tmp", O_RDONLY, 0);
		if (f == -1)
			exit(1);
		dup2(f, STDIN_FILENO);
		close(f);
		unlink("tmp");
	}
	else
	{
		if (access("tmp", F_OK))
			unlink("tmp");
		dup2(fdi, STDIN_FILENO);
	}
	dup2(fdo, STDOUT_FILENO);
	// close(fdi);
	// close(fdo);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
		err_print(127);
}

void	file_parent(int *pid)
{
	int	wstatus;
	int	code;

	waitpid(pid[0], &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			exit(code);
	}
}

void	file_process(int fdi, int fdo, char *cmd, t_redirs *rd)
{
	int		pid[2];
	char	**arg;

	arg = ft_split(cmd, ' ');
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		file_child(fdi, fdo, arg, rd);
	else
	{
		ft_free_arg(arg);
		file_parent(pid);
	}
}

void	reset(t_redirs *rd)
{
	rd->infile = NULL;
	rd->outfile = NULL;
	rd->append = NULL;
	rd->heredoc = NULL;
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

void	file(char *line, t_redirs *rd)
{
	int		fdi;
	int		fdo;
	char	*text;

	fdi = dup(0);
	fdo = dup(1);
	if (rd->heredoc && rd->lastin == 'h')
	{
		fdi = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		text = read_line(rd->heredoc);
		write(fdi, text, strlen(text));
		close(fdi);
	}
	if (rd->infile && rd->lastin == 'i')
		fdi = open(rd->infile, O_RDONLY, 0);
	if (rd->outfile && rd->lastout == 'o')
		fdo = open(rd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (rd->append && rd->lastout == 'a')
		fdo = open(rd->append, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fdi != -1 && fdo != -1)
		file_process(fdi, fdo, line, rd);
	else
		perror("File error");
	reset(rd);
}
