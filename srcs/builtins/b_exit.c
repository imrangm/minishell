/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:09:07 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 17:39:45 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	spaces_only_after(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	m_aredigits(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		i++;
		if (!str[i] || !ft_isdigit(str[i]))
			return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (ft_isspace(str[i]) && !spaces_only_after(str, i))
				return (0);
		}
		i++;
	}
	return (1);
}

static void	set_err_ec(t_data *data, char *msg, int num)
{
	ft_putendl_fd(msg, 2);
	data->last_exit_status = num;
}

static void	check_pipe_and_free(char **args, t_cmd *cmd, t_data *data)
{
	if (cmd->type != PCMD)
	{
		ft_free(data->line);
		free_and_exit(args, cmd, data);
	}
}

void	b_exit(char **args, t_cmd *cmd, t_data *data)
{
	int	arg_count;

	arg_count = ft_count2darr(args);
	if (arg_count == 2 && !ft_strcmp("--", args[1]))
		data->last_exit_status = 0;
	else if (arg_count == 3 && !ft_strcmp("--", args[1])
		&& m_aredigits(args[2]) && !ft_num_check(args[2]))
		data->last_exit_status = (unsigned char) ft_matoi(args[2]);
	else if (arg_count >= 3 && !ft_strcmp("--", args[1])
		&& m_aredigits(args[2]) && ft_num_check(args[2]))
		set_err_ec(data, "Error: numeric argument required", 255);
	else if (arg_count > 2 && m_aredigits(args[1]))
		set_err_ec(data, "Error: too many arguments", 1);
	else if (arg_count == 2 && m_aredigits(args[1]) && !ft_num_check(args[1]))
		data->last_exit_status = (unsigned char) ft_matoi(args[1]);
	else if ((arg_count == 2 && ft_num_check(args[1]))
		|| (arg_count == 2 && ft_strlen(args[1]) && !m_aredigits(args[1])))
		set_err_ec(data, "Error: numeric argument required", 255);
	else
		data->last_exit_status = 0;
	if (!data->last_exit_status)
		ft_putendl_fd("exit", 1);
	check_pipe_and_free(args, cmd, data);
}
