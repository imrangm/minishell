/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/19 15:43:05 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_parent_function(char *str)
{
	if (!cmp_cmd(str, "export"))
		return (1);
	else if (!cmp_cmd(str, "unset"))
		return (1);
	else if (!cmp_cmd(str, "exit"))
		return (1);
	else if (!cmp_cmd(str, "cd"))
		return (1);
	return (0);
}

char	**exec_cmd_parent(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!cmp_cmd(args[0], "export"))
	{
		b_export(args, data);
		return (data->envp);
	}
	else if (!cmp_cmd(args[0], "unset"))
	{
		b_unset(args, data);
		return (data->envp);
	}
	else if (!cmp_cmd(args[0], "exit"))
		b_exit(args, data);
	else if (!cmp_cmd(args[0], "cd"))
	{
		if (!args[1])
		{
			ft_putstr_fd("Error: second argument is required.\n", 2);
			data->last_exit_status = 1;
			return (data->envp);
		}
		b_cd(args[1]);
	}
	return (data->envp);
}