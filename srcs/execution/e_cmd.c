/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:15:14 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/09 16:07:30 by imustafa         ###   ########.fr       */
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

void	exec_cmd_parent(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "export"))
		b_export(args, data);
	else if (!ft_strcmp(args[0], "unset"))
		b_unset(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		b_exit(args, data);
	else if (!ft_strcmp(args[0], "cd"))
		b_cd(args, data);
}

int	exec_sys_cmd(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args, data);
	if (cmd_path && cmd_path[0])
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			ft_free_2d(args);
			free_data(data);
			ft_free(cmd_path);
			return (1);
		}
	}
	ft_free(cmd_path);
	return (0);
}

void	exec_cmd_child(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "export") && args[1])
		free_and_exit(args, data);
	else if (!ft_strcmp(args[0], "echo"))
		b_echo(args, data);
	else if (!ft_strcmp(args[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(args[0], "env"))
		b_env(data->envp, 0);
	else if (!ft_strcmp(args[0], "export"))
		b_env(data->envp, 1);
	else
		exec_cmd(args, data);
}
