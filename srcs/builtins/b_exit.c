/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:36:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/09 16:05:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_num_check(char *str)
{
	int					i;
	unsigned long long	result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str) - i > 19)
		return (1);
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (ft_strcmp(str, "-9223372036854775808") && result > 9223372036854775807)
		return (1);
	return (0);
}

void	b_exit(char *line, char **args, t_data *data)
{
	int	arg_count;

	arg_count = ft_count2darr(args);
	if (arg_count > 2 && ft_aredigits(args[1]))
	{
		ft_putendl_fd("Error: too many arguments", 2);
		data->last_exit_status = 1;
	}
	else if (arg_count == 2 && ft_aredigits(args[1]) && !ft_num_check(args[1]))
		data->last_exit_status = (unsigned char) ft_matoi(args[1]);
	else if (ft_num_check(args[1])
		|| (arg_count == 2 && ft_strlen(args[1]) && !ft_aredigits(args[1])))
	{
		ft_putendl_fd("Error: numeric argument required", 2);
		data->last_exit_status = 2;
	}
	else
		data->last_exit_status = 0;
	if (!data->last_exit_status)
		ft_putendl_fd("exit", 1);
	(void) line;
	// free(line);
	ft_free_2d(args);
	free_data(data);
	free_nodes(data->root);
	exit(data->last_exit_status);
}
