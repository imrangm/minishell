/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 18:01:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd_child(char **args, t_data *data)
{
	int	cmd_path;

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
		cmd_path = get_cmd_path(args, data); //! Work on this segment
		if (cmd_path)
		{
			if (execve(cmd_path, args, data->envp) == -1)
			{
				ft_free_arg(args);
				ft_free_arg(data->envp);
				return (-1);
			}
		}
	}
	ft_free_arg(args);
	ft_free_arg(data->envp);
	kill(getpid(), 9);
	return (0);
}