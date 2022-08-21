/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_ii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:23:06 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/21 16:53:23 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modify_env(char *var_name, char *value, t_data *data)
{
	int	i;

	i = 0;
	if (!env_exists(var_name, data))
	{
		append_env(var_name, value, data);
		return ;
	}
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], var_name,
				ft_counttochars(data->envp[i], '=', '\0')))
		{
			if (value)
			{
				ft_free(data->envp[i]);
				data->envp[i] = join_env_var_and_value(var_name, value);
			}
			break ;
		}
		i++;
	}
	ft_free(var_name);
	ft_free(value);
}

void	delete_env(char *var_name, t_data *data)
{
	int		i;
	int		j;
	char	*lhs;
	char	**envp_copy;

	i = ft_count2darr(data->envp);
	envp_copy = (char **) malloc(sizeof(char *) * i);
	if (!envp_copy)
		return ;
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		lhs = ft_substr(
				data->envp[i], 0, ft_counttochars(data->envp[i], '=', '\0'));
		if (ft_strcmp(lhs, var_name))
		{
			envp_copy[j] = ft_strdup(data->envp[i]);
			j++;
		}
		ft_free(lhs);
		i++;
	}
	envp_copy[j] = 0;
	ft_free_2d(data->envp);
	data->envp = envp_copy;
}

// void	delete_env(char *var_name, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*lhs;
// 	char	**envp;

// 	if (!env_exists(var_name, data))
// 	{
// 		data->last_exit_status = 0;
// 		return ;
// 	}
// 	i = 0;
// 	j = 0;
// 	envp = (char **) ft_calloc(sizeof(char *), ft_count2darr(data->envp));
// 	while (data->envp[i])
// 	{
// 		lhs = ft_substr(
// 				data->envp[i], 0, ft_counttochars(data->envp[i], '=', '\0'));
// 		if (ft_strcmp(lhs, var_name))
// 			envp[j] = ft_strdup(data->envp[i]);
// 		ft_free(lhs);
// 		i++;
// 		j++;
// 	}
// 	ft_free_2d(data->envp);
// 	data->envp = envp;
// }
