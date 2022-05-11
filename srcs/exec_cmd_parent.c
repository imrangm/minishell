/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 23:43:06 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_parent_function(char *str)
{
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	return (0);
}

char	**exec_cmd_parent(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
	{
		if (!args[1])
		{
			b_env(data->envp, 1);
			ft_free_arg(args);
			return (data->envp);
		}
		while (args[i]) //! Check syntax first before proceeding here because you can assign multiple vars and they can be unassigned
		{
			if (strchr(args[i], '='))
				data->envp = add_env(get_export_value_side(args[i], 1), get_export_value_side(args[i], 0), data->envp); //? export
			else
				data->envp = add_env(args[i], NULL, data->envp);
			i++;
		}
		ft_free_arg(args);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
	{
		if (!ft_strlen(args[1]))
		{
			ft_putstr_fd("Error: invalid number of arguments\n", 2);
			data->last_exit_status = 1;
			return (data->envp);
		}
		while (args[i])
		{
			unset_env(args[i], data->envp);
			i++;
		}
		ft_free_arg(args);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
	{
		if (args[1] && are_digits(args[1]) && !args[2])
			data->last_exit_status = (unsigned char) m_atoi(args[1]);
		else if (args[1] && ft_strlen(args[1]) && !are_digits(args[1]))
		{
			ft_putstr_fd("Error: numeric argument required\n", 2);
			data->last_exit_status = 255;
		}
		else if (args[0] && args[1] && args[2])
		{
			ft_putstr_fd("Error: too many arguments\n", 2);
			data->last_exit_status = 1;
		}
		else
			data->last_exit_status = 0;
		exit(data->last_exit_status);
	}
	else if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
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