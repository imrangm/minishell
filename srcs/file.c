/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:42:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/05 08:22:39 by imustafa         ###   ########.fr       */
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

void	file(char *line, t_redirs *rd)
{
	int		fdi;
	int		fdo;

	fdi = dup(0);
	fdo = dup(1);
	if (rd->infile && rd->lastin == 'i')
		fdi = open(rd->infile, O_RDONLY, 0);
	if (rd->outfile && rd->lastout == 'o')
		fdo = open(rd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (rd->append && rd->lastout == 'a')
		fdo = open(rd->append, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fdi == -1)
		perror("File not found");
	if (fdo == -1)
		perror("Could not create outfile");
	file_process(fdi, fdo, line);
}
