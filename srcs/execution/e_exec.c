/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/18 07:22:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quit_signal_handler(int signum)
{
	(void) signum;
	printf("Quit: 3\n");
	kill(g_child_pid, SIGQUIT);
}

static void	monitor_process(int pid, t_data *data)
{
	int	wstatus;
	int	code;

	g_child_pid = pid;
	signal(SIGQUIT, &quit_signal_handler);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code)
		{
			data->last_exit_status = code;
			strerror(code);
		}
		else
			data->last_exit_status = 0;
	}
}

char	*get_export_value_side(char *str, int lhs)
{
	int	i;
	int	rhs_start_index;

	i = 0;
	rhs_start_index = 0;
	while (str[i])
	{
		if ((str[i] == '=' || str[i] == '+') && lhs)
			return (ft_substr(str, 0, i));
		else if (str[i] == '=' && !lhs)
		{
			rhs_start_index = i;
			break ;
		}
		i++;
	}
	if (rhs_start_index)
		return (ft_substr(str, rhs_start_index + 1,
				ft_strlen(str) - rhs_start_index));
	return (NULL);
}

static void	create_child_process(char **args, t_execcmd *exec)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		exec->data->last_exit_status = 140;
		ft_putstr_fd("Error: Could not create child process\n", 2);
		return ;
	}
	if (pid == 0)
	{
		cmd(args, exec->data);
		free_and_exit(args, (t_cmd *) exec, exec->data);
	}
	else
		monitor_process(pid, exec->data);
}

void	scmd(t_execcmd *exec)
{
	char	**args;

	args = smart_split(exec->fcmd);
	if (is_builtin(args))
		builtin(args, exec->data);
	else
		create_child_process(args, exec);
	ft_free_2d(args);
}
