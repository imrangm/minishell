/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/05 14:17:08 by imustafa         ###   ########.fr       */
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
	// printf("%c\n", p->rd.lastin);
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
	// printf("i1: %d\n", i);
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
	// printf("i2: %d, data: %s, status: %c\n", *i, p[*i]->rd.heredoc, p[*i]->rd.lastin);
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
	// printf("infile: %s\n", p[i]->rd.infile);
	// printf("i3: %d, data: %s, status: %c\n", i, p[i]->rd.outfile, p[i]->rd.lastout);
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
** Main or parent process used to ensure all child
** processes have run successfully or otherwise
** throw an error and exit program
*/
void	parent(int nchild, int **pipes, int *pids)
{
	int	i;
	int	j;
	int	wstatus;
	int	code;

	j = 0;
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < nchild)
		waitpid(pids[i++], &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
			err_free_parent(pipes, pids);
	}
	if (access("tmp", F_OK) == 0)
		unlink("tmp");
	in_minishell_var(1);
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

/*
** Create the pipes and populate arg variable with program names;
** Passing them onto create_process function
*/
void	create_pipes(int nchild, char **cmd, t_pipe **p)
{
	int		i;
	int		**pipes;
	char	***arg;

	i = 0;
	arg = malloc (sizeof (char **) * nchild);
	while (i < nchild)
	{
		arg[i] = ft_split(cmd[i], ' ');
		i++;
	}
	i = 0;
	pipes = malloc(sizeof(int *) * (nchild));
	while (i < nchild)
	{
		pipes[i++] = malloc(sizeof(int) * 2);
		// if (!pipes[i])
		// 	err_free_pipex(pipes, arg, 3);
	}
	i = 0;
	while (i < nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
			err_free_pipex(pipes, arg);
		i++;
	}
	create_process (nchild, arg, pipes, p);
}

/*
** Count the number of pipe characters in the line
*/
int	count_pipes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '|')
			p++;
		i++;
	}
	return (p);
}

/*
** Split the line into different commands
*/
void	pipes(char *line, t_pipe **p)
{
	int		n;
	int		i;
	char 	**cmd;

	in_minishell_var(0);
	cmd = ft_split(line, '|');
	i = 0;
	while (cmd[i])
	{
		cmd[i] = cmd_copy(cmd[i]);
		i++;
	}
	n = count_pipes(line) + 1;
	create_pipes(n, cmd, p);
}
