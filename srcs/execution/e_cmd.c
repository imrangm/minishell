/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:15:14 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/21 17:47:06 by imustafa         ###   ########.fr       */
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

int	is_builtin(char **args)
{
	if (!ft_strcmp(args[0], "export"))
		return (1);
	else if (!ft_strcmp(args[0], "unset"))
		return (1);
	else if (!ft_strcmp(args[0], "exit"))
		return (1);
	else if (!ft_strcmp(args[0], "cd"))
		return (1);
	else if (!ft_strcmp(args[0], "echo"))
		return (1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(args[0], "env"))
		return (1);
	return (0);
}

void	builtin(char **args, t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(args[0], "export") && args[1])
		b_export(args, data);
	else if (!ft_strcmp(args[0], "unset"))
		b_unset(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		b_exit(args, cmd, data);
	else if (!ft_strcmp(args[0], "cd") && args[1])
		b_cd(args, data);
	else if (!ft_strcmp(args[0], "echo"))
		b_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(args[0], "env"))
		b_env(data->envp, 0);
	else if (!ft_strcmp(args[0], "export"))
		b_env(data->envp, 1);
}

void	cmd(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args, data);
	if (cmd_path && cmd_path[0])
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			data->last_exit_status = 127;
			ft_putstr_fd("Error: Unable to execute\n", 2);
			// ft_free(cmd_path);
			ft_free(data->line);
		}
	}
}

void	cmd_pipe(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args, data);
	if (cmd_path && cmd_path[0])
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			data->last_exit_status = 127;
			ft_putstr_fd("Error: Unable to execute\n", 2);
			// ft_free(cmd_path);
		}
	}
}
