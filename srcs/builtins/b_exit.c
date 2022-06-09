/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:36:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/07 15:52:27 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	b_exit(char **args, t_data *data)
{
	if (args[1] && ft_aredigits(args[1]) && !args[2])
		data->last_exit_status = (unsigned char) ft_matoi(args[1]);
	else if (args[1] && ft_strlen(args[1]) && !ft_aredigits(args[1]))
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
	free_2d(args);
	free_2d(data->envp);
	exit(data->last_exit_status);
}
