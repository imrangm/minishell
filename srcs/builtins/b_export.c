/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:16:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/07 15:52:29 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_env_values(char *lhs_arg, char *rhs_arg, t_data *data)
{
	char	*joined;

	joined = NULL;
	if (env_exists(lhs_arg, data->envp) && get_env_value(lhs_arg, data->envp))
	{
		joined = ft_strjoin(get_env_value(lhs_arg, data->envp), rhs_arg);
		data->envp = add_env(lhs_arg, joined, data->envp);
	}
	else if (!get_env_value(lhs_arg, data->envp))
		data->envp = add_env(lhs_arg, rhs_arg, data->envp);
}

int	is_in_plus_mode(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

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
		if (is_in_plus_mode(args[i]))
			join_env_values(get_export_value_side(args[i], 1),
				get_export_value_side(args[i], 0), data);
		else if (args[i] && strchr(args[i], '='))
			data->envp = add_env(get_export_value_side(args[i], 1),
					get_export_value_side(args[i], 0), data->envp);
		else
			data->envp = add_env(args[i], NULL, data->envp);
		i++;
	}
}
