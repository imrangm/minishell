/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:36:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/19 07:45:43 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_num_check(const char *str)
{
	int					i;
	unsigned long long	result;

	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str) - i > 19)
		return (1);
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (result > 9223372036854775807)
		return (1);
	return (0);
}

void	b_exit(char **args, t_data *data)
{
	if (args[1] && ft_aredigits(args[1]) && !args[2] && !ft_num_check(args[1]))
		data->last_exit_status = (unsigned char) ft_matoi(args[1]);
	else if (ft_num_check(args[1]))
	{
		// printf("args: %s\n", args[1]);
		ft_putstr_fd("Error: numeric argument required\n", 2);
		data->last_exit_status = 2;
	}
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
