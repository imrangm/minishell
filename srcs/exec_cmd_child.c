/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:15:14 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/27 14:41:00 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_other_cmd(char **args, t_data *data, char *cmd_path)
{
	cmd_path = get_cmd_path(args, data);
	if (cmd_path)
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			ft_free_arg(args);
			ft_free_arg(data->envp);
			free(cmd_path);
			return (1);
		}
	}
	free(cmd_path);
	return (0);
}

void	free_and_kill(char **args, char **envp)
{
	ft_free_arg(args);
	ft_free_arg(envp);
	kill(getpid(), 9);
}

int	exec_cmd_child(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!cmp_str(args[0], "export") && args[1])
		free_and_kill(args, data->envp);
	else if (!cmp_str(args[0], "echo"))
		b_echo(args, data);
	else if (!cmp_str(args[0], "pwd"))
		b_pwd(data);
	else if (!cmp_str(args[0], "env"))
		b_env(data->envp, 0);
	else if (!cmp_str(args[0], "export"))
		b_env(data->envp, 1);
	else
	{
		if (execute_other_cmd(args, data, cmd_path))
			return (-1);
	}
	free_and_kill(args, data->envp);
	return (0);
}
