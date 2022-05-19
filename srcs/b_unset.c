/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:34:30 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/19 15:42:55 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	b_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!ft_strlen(args[1]))
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		data->last_exit_status = 1;
		ft_free_arg(args);
		return ;
	}
	while (args[i])
	{
		unset_env(args[i], data->envp);
		i++;
	}
}