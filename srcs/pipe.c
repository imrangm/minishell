/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/25 22:33:54 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Child processes created to run the programs
*/
void	first_child(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = 0;
	j = 0;
	while (j < nchild - 1)
	{
		close(pipes[j][0]);
		if (i != j)
			close(pipes[j][1]);
		j++;
	}
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	if (execve(cmd_path(arg[0]), arg, environ) == -1)
	{
		ft_free(pipes);
		ft_free_arg(arg);
		err_print(127);
	}
}

void	mid_child(int *i, int nchild, char **arg, int **pipes)
{
	int			j;
	extern char	**environ;

	j = 0;
	while (j < nchild - 1)
	{
		if (*i - 1 != j)
			close(pipes[j][0]);
		if (*i != j)
			close(pipes[j][1]);
		j++;
	}
	dup2(pipes[(*i) - 1][0], STDIN_FILENO);
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

void	last_child(int nchild, char **arg, int **pipes)
{
	int			i;
	int			j;
	extern char	**environ;

	i = nchild - 1;
	j = 0;
	while (j < nchild - 1)
	{
		if (i - 1 != j)
			close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	dup2(pipes[i - 1][0], STDIN_FILENO);
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
	in_minishell_var(1);
}

/*
** Create the processes to run the number of programs passed by user
*/
void	create_process(int nchild, char ***arg, int **pipes)
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
				first_child(nchild, arg[i], pipes);
			if (i < nchild - 1)
				mid_child(&i, nchild, arg[i], pipes);
			if (i == nchild - 1)
				last_child(nchild, arg[i], pipes);
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
void	create_pipes(int nchild, char **cmd)
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
	create_process (nchild, arg, pipes);
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
void	pipes(char *line)
{
	int		n;
	char 	**cmd;

	in_minishell_var(0);
	cmd = ft_split(line, '|');
	n = count_pipes(line) + 1;
	create_pipes(n, cmd);
}