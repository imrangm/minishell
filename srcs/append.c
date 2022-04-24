/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:44:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/24 17:28:36 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_child(int fdo, char **arg)
{
	extern char	**environ;

	dup2(fdo, STDOUT_FILENO);
	// close(fdo);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
		err_print(127);
}

void	append_parent(int *pid)
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

void	append_process(int fdo, char *cmd)
{
	int		pid[2];
	char	**arg;

	arg = ft_split(cmd, ' ');
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		append_child(fdo, arg);
	else
	{
		ft_free_arg(arg);
		append_parent(pid);
	}
}

void	append(char *line)
{
	char	**split;
	char	*file;
	int		fdo;

	split = chars_split(line, ">>");
	file = ft_strtrim(split[1], " ");
	fdo = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fdo == -1)
		exit (1);
	append_process(fdo, split[0]);
}