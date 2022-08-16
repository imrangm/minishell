/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_ii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:23:06 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 18:28:21 by nmadi            ###   ########.fr       */
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

void	free_block(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_counttochars(envp[i], '=', '\0')))
		{
			ft_free(envp[i]);
			break ;
		}
		i++;
	}
}

void	delete_env(char *var_name, t_data *data)
{
	int		i;
	int		c;
	char	*tmp;
	char	**new_envp;

	i = 0;
	if (!env_exists(var_name, data))
		return ;
	c = ft_count2darr(data->envp);
	new_envp = (char **) ft_calloc(sizeof(char *), c + 1);
	if (!new_envp)
		return ;
	while (i < c)
	{
		tmp = ft_substr(data->envp[i], 0,
				ft_counttochars(data->envp[i], '=', '\0') + 1);
		if (ft_strcmp(var_name, tmp))
			new_envp[i] = ft_strdup(data->envp[i]);
		ft_free(tmp);
		i++;
	}
	new_envp[i] = 0;
	ft_free_2d(data->envp);
	data->envp = new_envp;
}
