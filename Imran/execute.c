/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imran             #+#    #+#             */
/*   Updated: 2022/04/08 17:44:25 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

void	err_print(int error)
{
	perror("Error");
	exit (error);
}

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

void	process(int pid)
{
	int	wstatus;
	int	code;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code == 0)
			exit (EXIT_SUCCESS);
		else
			exit(code);
	}
}

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
		process(pid);
	}
}