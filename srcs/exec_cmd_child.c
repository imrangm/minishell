/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:15:14 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/22 15:43:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd_child(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!cmp_str(args[0], "echo"))
		b_echo(args, data);
	else if (!cmp_str(args[0], "pwd"))
		b_pwd(data);
	else if (!cmp_str(args[0], "env"))
		b_env(data->envp, 0);
	else if (!cmp_str(args[0], "export"))
		b_env(data->envp, 1);
	else
	{
		cmd_path = get_cmd_path(args, data);
		if (cmd_path)
		{
			if (execve(cmd_path, args, data->envp) == -1)
			{
				ft_free_arg(args);
				ft_free_arg(data->envp);
				free(cmd_path);
				return (-1);
			}
		}
		free(cmd_path);
	}
	ft_free_arg(args);
	ft_free_arg(data->envp);
	kill(getpid(), 9);
	return (0);
}