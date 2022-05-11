/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 16:17:59 by nmadi            ###   ########.fr       */
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
	in_minishell_var(0);
}

/*
** creating new process and using it to execute a shell command;
** execve uses cmd_path in find.c to check if the command exists
** and return its path
*/
void	master_execute(char *line, t_data *data)
{
	char		**arg;
	int			pid;

	in_minishell_var(0);
	line = cmd_copy(line);
	arg = ft_split(line, ' ');
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (exec_cmd(arg, data) == -1)
			err_print(127);
	}
	else
	{
		ft_free_arg(arg);
		monitor(pid);
	}
}