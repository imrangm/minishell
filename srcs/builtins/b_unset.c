/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:34:30 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/23 18:13:45 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(char *arg, t_data *data)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("' is not a valid identifier", 2);
	data->last_exit_status = 1;
	return (0);
}

int	validate_arg(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == '_')
		i++;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (handle_error(arg, data));
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (handle_error(arg, data));
		i++;
	}
	return (1);
}

void	b_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (validate_arg(args[i], data))
		{
			if (ft_strcmp(args[i], "_"))
			{
				if (env_exists(args[i], data))
					delete_env(args[i], data);
			}
		}
		i++;
	}
}
