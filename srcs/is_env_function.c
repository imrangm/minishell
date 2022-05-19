/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:11:42 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/19 15:12:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_env_function(char **args, t_data *data)
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
		while (args[i])
		{
			if (strchr(args[i], '='))
				data->envp = add_env(get_export_value_side(args[i], 1)
							, get_export_value_side(args[i], 0), data->envp); //? export
			else
				data->envp = add_env(args[i], NULL, data->envp);
			i++;
		}
		ft_free_arg(args);
		ft_free_arg(data->envp);
		return (data->envp);
	}
	else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
	{
		if (!ft_strlen(args[1]))
		{
			ft_putstr_fd("Error: invalid number of arguments\n", 2);
			data->last_exit_status = 1;
			ft_free_arg(args);
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
}