/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:16:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/13 18:32:05 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_env_values(char *lhs_arg, char *rhs_arg, t_data *data)
{
	char	*joined;

	joined = NULL;
	if (env_exists(lhs_arg, data) && get_env_value(lhs_arg, data))
	{
		joined = ft_strjoin(get_env_value(lhs_arg, data), rhs_arg);
		modify_env(lhs_arg, joined, data);
	}
	else if (!get_env_value(lhs_arg, data))
		modify_env(lhs_arg, rhs_arg, data);
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
	int	f;

	i = 1;
	f = 0;
	if (!args[1])
	{
		b_env(data->envp, 1);
		return ;
	}
	while (args[i])
	{
		f = ft_strncmp(args[i], "_", ft_counttochars(args[i], '=', '\0'));
		if (is_in_plus_mode(args[i]) && f)
			join_env_values(get_export_value_side(args[i], 1),
				get_export_value_side(args[i], 0), data);
		else if (strchr(args[i], '=') && f)
			modify_env(get_export_value_side(args[i], 1),
				get_export_value_side(args[i], 0), data);
		else if (f)
			modify_env(args[i], NULL, data);
		i++;
	}
}
