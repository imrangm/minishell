/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:45:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/27 14:35:54 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_pipe(t_pipe *p)
{
	int		fdi;
	char	*text;

	fdi = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdi == -1)
		exit (1);
	text = read_line(p->rd.heredoc);
	write(fdi, text, strlen(text));
	close(fdi);
	if (p->rd.lastin == 'h')
	{
		fdi = open("tmp", O_RDONLY, 0);
		if (fdi == -1)
			p[0].data->last_exit_status = 1;
		dup2(fdi, STDIN_FILENO);
	}
	else
	{
		fdi = open(p->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
	close(fdi);
}

int	redir_in(t_pipe **p, int i)
{
	int	fd;

	fd = 0;
	if (p[i]->rd.heredoc)
	{
		here_pipe(p[i]);
		return (1);
	}
	else if (p[i]->rd.infile && p[i]->rd.lastin == 'i')
	{
		fd = open(p[i]->rd.infile, O_RDONLY);
		if (fd == -1)
			err_kill_process(p);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}

int	redir_out(t_pipe **p, int i)
{
	int	fd;

	if (p[i]->rd.outfile && p[i]->rd.lastout == 'o')
	{
		fd = open(p[i]->rd.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			err_kill_process(p);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	else if (p[i]->rd.append && p[i]->rd.lastout == 'a')
	{
		fd = open(p[i]->rd.append, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			err_kill_process(p);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}

void	parent(char ***arg, int **pipes, int *pids, t_pipe **p)
{
	int	i;
	int	wstatus;
	int	code;

	i = 0;
	wstatus = 0;
	while (i < p[0]->nchild - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < p[0]->nchild)
		waitpid(pids[i++], &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			p[0]->data->last_exit_status = code;
	}
	if (access("tmp", F_OK))
		unlink("tmp");
	ps_free(arg, pipes, pids, p);
	in_minishell_var(1);
}

void	create_process(char ***arg, int **pipes, t_pipe **p)
{
	int	*pids;
	int	i;

	i = 0;
	pids = malloc (sizeof(int) * p[0]->nchild);
	if (!pids)
		perror("Malloc failed");
	while (i < p[0]->nchild)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			err_print(4, p[0]->data);
		if (pids[i] == 0)
		{
			if (i == 0)
				first_child(arg[i], pipes, p);
			if (i < p[0]->nchild - 1)
				mid_child(&i, arg[i], pipes, p);
			if (i == p[0]->nchild - 1)
				last_child(arg[i], pipes, p);
		}
		i++;
	}
	parent(arg, pipes, pids, p);
}
