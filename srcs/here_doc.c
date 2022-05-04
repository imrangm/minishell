/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:04:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/04 20:14:20 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
** Setting up here_doc operator in bash shell 
*/

void	here_child(char **arg)
{
	extern char	**environ;
	int			f;

	f = open("tmp", O_RDONLY, 0);
	if (f == -1)
		exit(1);
	dup2(f, STDIN_FILENO);
	close(f);
	unlink("tmp");
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
		err_print(127);
}

void	here_parent(int pid)
{
	int	wstatus;
	int	code;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			exit(code);
	}
}

void	here_process(char *cmd)
{
	int		pid;
	char	**arg;

	arg = ft_split(cmd, ' ');
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		here_child(arg);
	else
	{
		ft_free_arg(arg);
		here_parent(pid);
	}
}

static char	*read_line(char *lim)
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

void	here_ops(char *line, t_redirs *rd)
{
	char	*text;
	int		fdi;

	fdi = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdi == -1)
		exit (1);
	text = read_line(rd->heredoc);
	write(fdi, text, strlen(text));
	close(fdi);
	here_process(line);
}