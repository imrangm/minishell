/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/21 16:35:12 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_child_pid;

static void	signal_handler_iii(int signum)
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
	signal(SIGQUIT, &signal_handler_iii);
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

static void	create_child_process(char **args, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		data->last_exit_status = 140;
		ft_free_2d(args);
		ft_putstr_fd("Error: Could not create child process\n", 2);
		return ;
	}
	if (pid == 0)
	{
		if (exec_cmd_child(args, data))
		{
			ft_putstr_fd("Error: Command not found\n", 2);
			data->last_exit_status = 127;
		}
		free_data(data);
	}
	else
		monitor_process(pid, data);
}

void	master_execute(char *line, t_data *data)
{
	char	**args;

	args = smart_split(line);
	if (is_parent_function(args))
	{
		exec_cmd_parent(line, args, data);
		ft_free_2d(args);
	}
	else
	{
		create_child_process(args, data);
		ft_free_2d(args);
	}
}
