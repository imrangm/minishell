/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:20:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/15 20:08:53 by imustafa         ###   ########.fr       */
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
		if (code != 0)
			err_free_parent(pipes, pids);
	}
	if (access("tmp", F_OK) == 0)
		unlink("tmp");
	in_minishell_var(1);
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
	}
	i = 0;
	while (i < nchild - 1)
	{
		if (pipe(pipes[i]) == -1)
			err_free_pipex(pipes, arg);
		i++;
	}
	create_process(nchild, arg, pipes, p);
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
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd[i] = set_cmd(cmd[i], cmd[i]);
		i++;
	}
	create_pipes(n, cmd, p);
	ft_free_arg(cmd);
}
