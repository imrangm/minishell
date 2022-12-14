/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 17:39:21 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error(t_node *node, t_data *data)
{
	if (node->type == 1)
	{
		check_error(node->left, data);
		check_error(node->right, data);
	}
	else if (node->type == 2)
	{
		ft_putstr_fd(node->value, 2);
		ft_putchar_fd('\n', 2);
		data->last_exit_status = 1;
		data->error = 1;
		return (1);
	}
	return (0);
}

void	free_and_exit(char **args, t_cmd *cmd, t_data *data)
{
	ft_free_2d(args);
	free_data(data);
	free_nodes(data->root);
	ft_free(cmd);
	exit(data->last_exit_status);
}

int	ft_num_check(char *str)
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
