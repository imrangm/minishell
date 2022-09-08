/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:04:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/08 02:37:10 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_and_exit(char **args, t_data *data)
{
	ft_free_2d(args);
	free_data(data);
	free_nodes(data->root);
	exit(data->last_exit_status);
}

void	exec_builtin(char *line, char **args, t_data *data)

{
	if (!ft_strcmp(args[0], "export") && args[1])
		b_export(args, data);
	else if (!ft_strcmp(args[0], "unset"))
		b_unset(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		b_exit(line, args, data);
	else if (!ft_strcmp(args[0], "cd"))
		b_cd(args, data);
	else if (!ft_strcmp(args[0], "echo"))
		b_echo(args, data);
	else if (!ft_strcmp(args[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(args[0], "env"))
		b_env(data->envp, 0);
	else if (!ft_strcmp(args[0], "export"))
		b_env(data->envp, 1);
}

void	exec_cmd(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args, data);
	if (cmd_path && cmd_path[0])
	{
		if (execve(cmd_path, args, data->envp) == -1)
		{
			data->last_exit_status = 127;
			ft_putstr_fd("Error: Unable to execute\n", 2);
		}
	}
}
