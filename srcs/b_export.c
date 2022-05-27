/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:16:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/27 14:41:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	b_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		b_env(data->envp, 1);
		return ;
	}
	while (args[i])
	{
		if (strchr(args[i], '='))
			data->envp = add_env(get_export_value_side(args[i], 1),
					get_export_value_side(args[i], 0), data->envp);
		else
			data->envp = add_env(args[i], NULL, data->envp);
		i++;
	}
}
