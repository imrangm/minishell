/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:43:35 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:11:00 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 1;
	if (!ft_strcmp(str, "-n"))
		return (1);
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	b_echo(char **args, t_data *data)
{
	int	i;
	int	normal_mode;

	i = 1;
	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	normal_mode = !is_n_flag(args[1]);
	while (args[i] && is_n_flag(args[i]))
		i++;
	while (args[i])
	{
		if (!args[i + 1] && !normal_mode)
			printf("%s", args[i]);
		else if (!args[i + 1] && normal_mode)
			printf("%s\n", args[i]);
		else
			printf("%s ", args[i]);
		i++;
	}
	data->last_exit_status = 0;
	return (0);
}
