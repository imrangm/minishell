/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/10 19:34:47 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_child(int fdi, int fdo, char **arg)
{
	extern char	**environ;

	dup2(fdi, STDIN_FILENO);
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

void	file_process(int fdi, int fdo, char *cmd)
{
	int		pid[2];
	char	**arg;

	arg = ft_split(cmd, ' ');
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		file_child(fdi, fdo, arg);
	else
	{
		ft_free_arg(arg);
		file_parent(pid);
	}
}

int	find_sym(char **line, char sym)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (ft_strncmp(line[i], &sym, 1) == 0)
			return (i);
	}
	return (0);
}

void	file(char *line)
{
	int		fdi;
	int		fdo;
	int		i;
	char	**line_split;
	// int		infile;
	// int		outfile;
	// char	**line_ref;

	fdi = 0;
	fdo = 1;
	line_split = chars_split(line, "<>");
	// line_ref = ft_split(line, ' ');
	// infile = find_sym(line_ref, '<');
	// outfile = find_sym(line_ref, '>');
	// printf("%d: %d\n", infile, outfile);
	i = 0;
	while (line_split[i] != NULL)
	{
		line_split[i] = ft_strtrim(line_split[i], " ");
		// printf("%s\n", line_split[i]);
		i++;
	}
	if (ft_strchr(line, '<') && ft_strchr(line, '>'))
	{
		fdi = open(line_split[1], O_RDONLY, 0);
		fdo = open(line_split[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (ft_strchr(line, '<') && !ft_strchr(line, '>'))
		fdi = open(line_split[1], O_RDONLY, 0);
	if (ft_strchr(line, '>') && !ft_strchr(line, '<'))
		fdo = open(line_split[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdi == -1)
		perror("File not found");
	if (fdo == -1)
		perror("Could not create outfile");
	file_process(fdi, fdo, line_split[0]);
}
