/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 18:42:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_parent_function(char *str)
{
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}

char	**exec_cmd_parent(char **args, t_data *data)
{
	if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
	{
		data->envp = add_env(get_export_value_side(args[1], 1), get_export_value_side(args[1], 0), data->envp); //? export
		ft_free_arg(args);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
	{
		if (!ft_strlen(args[1]))
		{
			ft_putstr_fd("Error: Unset takes\n", 2);
			data->last_exit_status = 0;
			return (data->envp);
		}
		unset_env(args[1], data->envp); //? unset
		ft_free_arg(args);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
	{
		b_env(data->envp); //? env
		ft_free_arg(args);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
	{
		if (args[1] && ft_strlen(args[1])) // add a are_digits check function
		{
			if (m_atoi(args[1]) == -1)
				return (data->envp);
			else if (m_atoi(args[1]) >= 0 && m_atoi(args[1]) <= 255)
				data->last_exit_status = m_atoi(args[1]);
			else if (!(m_atoi(args[1]) >= 0 && m_atoi(args[1]) <= 255))
			{
				ft_putstr_fd("Error: Exit code must be anywhere between 0-255.\n", 2);
				return (data->envp);
			}
		}
		else
			data->last_exit_status = 0;
		exit(data->last_exit_status);
	}
	return (data->envp);
}