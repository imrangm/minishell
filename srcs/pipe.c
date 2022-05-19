/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/19 14:13:00 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (access("tmp", F_OK))
			unlink("tmp");
		if (code != 0)
			err_free_parent(pipes, pids);
	}
	no_err_free_parent(pipes, pids);
	in_minishell_var(1);
}

/*
** Create the pipes to communicate between child processes
*/
static void	create_pipes(int nchild, char ***arg, t_pipe **p)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * (nchild));
	if (!pipes)
		perror("Malloc failed");
	while (i < nchild)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			perror("Malloc failed");
		i++;
	}
	i = 0;
	while (i < nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
			err_free_process(pipes, arg);
		i++;
	}
	create_process(nchild, arg, pipes, p);
}

/*
** Populate arg variable with program names
*/
static void	create_arg(int nchild, char **cmd, t_pipe **p)
{
	int		i;
	char	***arg;

	i = 0;
	arg = malloc (sizeof(char **) * nchild);
	if (!arg)
		perror("Malloc failed");
	while (i < nchild)
	{
		arg[i] = ft_split(cmd[i], ' ');
		i++;
	}
	ft_free_arg(cmd);
	create_pipes(nchild, arg, p);
}

/*
** Split the line into different commands
*/
void	pipes(char *line, t_pipe **p)
{
	int		n;
	int		i;
	char	**cmd;

	in_minishell_var(0);
	n = count_pipes(line) + 1;
	i = 0;
	cmd = ft_split_pp(line, '|');
	while (cmd[i])
	{
		cmd[i] = find_cmd(cmd[i]);
		i++;
	}
	create_arg(n, cmd, p);
}
