/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:15:14 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/15 17:47:20 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_parent_function(char **args)
{
	if (!ft_strcmp(args[0], "export") && args[1])
		return (1);
	else if (!ft_strcmp(args[0], "unset"))
		return (1);
	else if (!ft_strcmp(args[0], "exit"))
		return (1);
	else if (!ft_strcmp(args[0], "cd"))
		return (1);
	return (0);
}

void	exec_cmd_parent(char *line, char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "export"))
		b_export(args, data);
	else if (!ft_strcmp(args[0], "unset"))
		b_unset(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		b_exit(line, args, data);
	else if (!ft_strcmp(args[0], "cd"))
		b_cd(args, data);
}

static int	exec_sys_cmd(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args, data);
	if (cmd_path && cmd_path[0])
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			free_2d(args);
			free_2d(data->envp);
			safe_free(cmd_path);
			return (1);
		}
	}
	safe_free(cmd_path);
	return (0);
}

static void	free_and_kill(char **args, char **envp)
{
	free_2d(args);
	free_2d(envp);
	exit(0);
}

int	exec_cmd_child(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "export") && args[1])
		free_and_kill(args, data->envp);
	else if (!ft_strcmp(args[0], "echo"))
		b_echo(args, data);
	else if (!ft_strcmp(args[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(args[0], "env"))
		b_env(data->envp, 0);
	else if (!ft_strcmp(args[0], "export"))
		b_env(data->envp, 1);
	else
	{
		if (exec_sys_cmd(args, data))
			return (-1);
	}
	free_and_kill(args, data->envp);
	return (0);
}
