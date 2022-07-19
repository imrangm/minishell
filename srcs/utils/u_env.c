/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/19 11:24:38 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strchr(data->envp[i], '='))
			return (ft_strdup(" "));
		if (!ft_strncmp(str, data->envp[i], ft_counttochars(str, '+', '='))
			&& data->envp[i][ft_strlen(str)] == '=')
			return (ft_substr(ft_strchr(data->envp[i], '='),
					1, ft_strlen(ft_strchr(data->envp[i], '='))));
		i++;
	}
	return (NULL);
}

int	env_exists(char *var_name, t_data *data)
{
	int		i;

	i = 0;
	while (data->envp && data->envp[i])
	{
		if (ft_strchr(data->envp[i], '='))
		{
			if (!ft_strncmp(var_name, data->envp[i],
					ft_counttochars(data->envp[i], '=', '\0'))
				&& data->envp[i][ft_strlen(var_name)] == '=')
				return (1);
		}
		else if (!ft_strcmp(var_name, data->envp[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*join_env_var_and_value(char *var_name, char *value)
{
	char	*equal;
	char	*var_name_and_equal;
	char	*full_env_entry;

	if (!value)
		return (ft_strdup(var_name));
	equal = (char *) malloc(sizeof(char) * 2);
	if (!equal)
		return (NULL);
	equal[0] = '=';
	equal[1] = '\0';
	var_name_and_equal = ft_strjoin(var_name, equal);
	free(equal);
	full_env_entry = ft_strjoin(var_name_and_equal, value);
	free(var_name_and_equal);
	return (full_env_entry);
}

char	**clone_env(char **envp, int extra_slot)
{
	int		i;
	char	**envp_copy;

	i = ft_count2darr(envp);
	envp_copy = (char **) malloc(sizeof(char *) * (i + 1 + extra_slot));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = 0;
	if (extra_slot == 1)
		envp_copy[++i] = 0;
	return (envp_copy);
}

void	append_env(char *var_name, char *value, t_data *data)
{
	int		i;
	char	**new_envp;

	i = ft_count2darr(data->envp);
	new_envp = clone_env(data->envp, 1);
	if (!new_envp)
		return ;
	if (value != NULL)
		new_envp[i] = join_env_var_and_value(var_name, value);
	else
		new_envp[i] = ft_strdup(var_name);
	free_2d(data->envp);
	data->envp = new_envp;
	safe_free(var_name);
	safe_free(value);
}
