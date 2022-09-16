/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:16:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/12 11:07:58 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_env_values(char *lhs_arg, char *rhs_arg, t_data *data)
{
	char	*joined;
	char	*env_value;

	joined = NULL;
	env_value = get_env_value(lhs_arg, data);
	if (env_value && env_exists(lhs_arg, data))
	{
		joined = ft_strjoin(env_value, rhs_arg);
		ft_free(env_value);
		ft_free(rhs_arg);
		modify_env(lhs_arg, joined, data);
	}
	else if (!get_env_value(lhs_arg, data))
		modify_env(lhs_arg, rhs_arg, data);
	else
		append_env(lhs_arg, rhs_arg, data);
}

static int	is_in_plus_mode(char *str)
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

static int	check_args(char **args, t_data *data)
{
	if (pc_export(args))
	{
		data->last_exit_status = 1;
		return (1);
	}
	if (!args[1])
	{
		b_env(data->envp, 1);
		return (1);
	}
	return (0);
}

void	b_export(char **args, t_data *data)
{
	int		i;
	int		f;
	char	*left;
	char	*right;

	i = 1;
	f = 0;
	if (check_args(args, data))
		return ;
	while (args[i])
	{
		f = ft_strncmp(args[i], "_", ft_counttochars(args[i], '=', '\0'));
		left = get_export_value_side(args[i], 1);
		right = get_export_value_side(args[i], 0);
		if (is_in_plus_mode(args[i]) && f)
			join_env_values(left, right, data);
		else if (ft_strchr(args[i], '=') && f)
			modify_env(left, right, data);
		else if (f)
			modify_env(ft_strdup(args[i]), NULL, data);
		i++;
	}
}
