/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/22 12:00:25 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	monitor_process(int pid, t_data *data)
{
	int	wstatus;
	int	code;

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
	in_minishell_var(0);
}

char	*get_export_value_side(char *str, int lhs)
{
	int	i;
	int	rhs_start_index;

	i = 0;
	rhs_start_index = 0;
	while (str[i])
	{
		if (str[i] == '=' && lhs)
			return (ft_substr(str, 0, i));
		else if (str[i] == '=' && !lhs)
		{
			rhs_start_index = i;
			break ; //! Added for a=b=c
		}
		i++;
	}
	if (rhs_start_index)
		return (ft_substr(str, rhs_start_index + 1, ft_strlen(str) - rhs_start_index));
	return (NULL);
}

static void create_child_process(char **args, t_data *data)
{
	int	pid;
	pid = fork();
	if (pid == -1)
	{
		data->last_exit_status = 1;
		ft_free_arg(args);
		ft_putstr_fd("Error: Could not create child process\n", 2);
		// ft_free_arg(data->envp);
		// exit(data->last_exit_status);
		return ;
	}
	if (pid == 0)
	{
		if (exec_cmd_child(args, data) == -1)
		{
			ft_putstr_fd("Error: Command not found\n", 2);
			data->last_exit_status = 127;
		}
	}
	else
	{
		ft_free_arg(args);
		monitor_process(pid, data);
	}
}

void	master_execute(char *line, t_data *data)
{
	char	**args;

	in_minishell_var(0);
	args = ft_split(line, ' '); //TODO Create a better ft_split()
	if (is_parent_function(args))
	{
		data->envp = exec_cmd_parent(args, data); //TODO Implement wait() or waitpid()
		ft_free_arg(args);
	}
	else
		create_child_process(args, data);
}