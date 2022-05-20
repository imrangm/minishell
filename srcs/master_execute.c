/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/20 13:03:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Main or parent process to monitor child process
*/
void	monitor(int pid, t_data *data)
{
	int	wstatus;
	int	code;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		code = WEXITSTATUS(wstatus);
		if (code != 0)
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

/*
** creating new process and using it to execute a shell command;
** execve uses cmd_path in find.c to check if the command exists
** and return its path
*/
void	master_execute(char *line, t_data *data)
{
	char	**args;
	int		pid;

	in_minishell_var(0);
	args = ft_split(line, ' ');
	if (is_parent_function(args))
	{
		data->envp = exec_cmd_parent(args, data); //! Implement wait() or waitpid()
		ft_free_arg(args);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			data->last_exit_status = 1;
			exit(data->last_exit_status); //! Discuss this
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
			monitor(pid, data);
		}
	}
}