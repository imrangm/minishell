/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/23 05:36:56 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char		**arg;
	int			pid;

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