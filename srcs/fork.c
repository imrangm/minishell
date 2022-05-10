/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:45:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/10 21:50:56 by imustafa         ###   ########.fr       */
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
			exit(1);
		dup2(fdi, STDIN_FILENO);
	}
	else
	{
		fdi = open(p->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
}

/*
** this function is not yet assigned and need to be thought through.
*/
void	assign_fd(int fd, t_pipe **p, int *i)
{

	if (p[*i]->rd.heredoc)
		here_pipe(p[*i]);
	else if (p[*i]->rd.infile && p[*i]->rd.lastin == 'i')
	{
		fd = open(p[*i]->rd.infile, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
	else
		fd = 0;
	if (p[*i]->rd.outfile && p[*i]->rd.lastout == 'o')
	{
		fd = open(p[*i]->rd.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (p[*i]->rd.append && p[*i]->rd.lastout == 'a')
	{
		fd = open(p[*i]->rd.append, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else 
		fd = 1;
}

/*
** Child processes created to run the programs
*/
void	first_child(int nchild, char **arg, int **pipes, t_pipe **p)
{
	int			i;
	int			j;
	int			fdi;
	int			fdo;
	extern char	**environ;

	i = 0;
	j = 0;
	fdi = dup(0);
	fdo = dup(1);
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	if (p[i]->rd.heredoc)
		here_pipe(p[i]);
	else if (p[i]->rd.infile && p[i]->rd.lastin == 'i')
	{
		fdi = open(p[i]->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
	if (p[i]->rd.outfile && p[i]->rd.lastout == 'o')
	{
		fdo = open(p[i]->rd.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	else if (p[i]->rd.append && p[i]->rd.lastout == 'a')
	{
		fdo = open(p[i]->rd.append, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	else 
		dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	mid_child(int *i, int nchild, char **arg, int **pipes, t_pipe **p)
{
	int			j;
	int			fdi;
	int			fdo;
	extern char	**environ;

	j = 0;
	fdi = dup(0);
	fdo = dup(1);
	while (j < nchild - 1)
	{
		if (*i - 1 != j)
			close(pipes[j][0]);
		if (*i != j)
			close(pipes[j][1]);
		j++;
	}
	if (p[*i]->rd.heredoc)
		here_pipe(p[*i]);
	else if (p[*i]->rd.infile && p[*i]->rd.lastin == 'i')
	{
		fdi = open(p[*i]->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
	else
		dup2(pipes[(*i) - 1][0], STDIN_FILENO);
	if (p[*i]->rd.outfile)
	{
		fdo = open(p[*i]->rd.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	else if (p[*i]->rd.append && p[*i]->rd.lastout == 'a')
	{
		fdo = open(p[*i]->rd.append, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	else
		dup2(pipes[*i][1], STDOUT_FILENO);
	close(pipes[(*i) - 1][0]);
	close(pipes[*i][1]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	last_child(int nchild, char **arg, int **pipes, t_pipe **p)
{
	int			i;
	int			j;
	int			fdi;
	int			fdo;
	extern char	**environ;

	i = nchild - 1;
	j = 0;
	fdi = dup(0);
	fdo = dup(1);
	while (j < nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	if (p[i]->rd.heredoc)
		here_pipe(p[i]);
	else if (p[i]->rd.infile && p[i]->rd.lastin == 'i')
	{
		fdi = open(p[i]->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (p[i]->rd.outfile && p[i]->rd.lastout == 'o')
	{
		fdo = open(p[i]->rd.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	else if (p[i]->rd.append && p[i]->rd.lastout == 'a')
	{
		fdo = open(p[i]->rd.append, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fdo, STDOUT_FILENO);
	}
	close(pipes[i - 1][0]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

/*
** Create the processes to run the number of programs passed by user
*/
void	create_process(int nchild, char ***arg, int **pipes, t_pipe **p)
{
	int	*pids;
	int	i;

	i = 0;
	pids = malloc (sizeof(int) * nchild);
	while (i < nchild)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			err_print(4);
		if (pids[i] == 0)
		{
			if (i == 0)
				first_child(nchild, arg[i], pipes, p);
			if (i < nchild - 1)
				mid_child(&i, nchild, arg[i], pipes, p);
			if (i == nchild - 1)
				last_child(nchild, arg[i], pipes, p);
		}
		i++;
	}
	ft_free_args(arg);
	parent(nchild, pipes, pids);
}