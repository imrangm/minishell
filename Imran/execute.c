/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imran             #+#    #+#             */
/*   Updated: 2022/04/09 18:19:22 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

/*
** Print error from the system and exit program
*/
void	err_print(int error)
{
	perror("Error");
	exit (error);
}

/*
** free memory allocated through ft_split
*/
void	ft_free_arg(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free (arr);
	arr = NULL;
}

/*
** Main or parent process to monitor child process
*/
void	monitor(int pid)
{
	int	wstatus;
	int	code;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			strerror(code);
	}
}

/*
** creating new process and using it to execute a shell command;
** execve uses cmd_path in find.c to check if the command exists
** and return its path
*/
void	execute(char *line)
{
	extern char	**environ;
	char	**arg;
	int		pid;

	arg = ft_split(line, ' ');
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (execve(cmd_path(arg[0]), arg, environ) == -1)
			err_print(127);
	}
	else
	{
		ft_free_arg(arg);
		monitor(pid);
	}
}