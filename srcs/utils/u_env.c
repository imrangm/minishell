/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/13 18:27:39 by nmadi            ###   ########.fr       */
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
			if (!ft_strncmp(var_name, data->envp[i], ft_counttochars(data->envp[i], '=', '\0'))
				&& data->envp[i][ft_strlen(var_name)] == '=')
				return (1);
		}
		if (!ft_strcmp(var_name, data->envp[i]))
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
	safe_free(equal);
	full_env_entry = ft_strjoin(var_name_and_equal, value);
	safe_free(var_name_and_equal);
	return (full_env_entry);
}

char	**clone_env(char **envp, int extra_slot)
{
	int		i;
	char	**envp_copy;

	i = 0;
	while (envp && envp[i])
		i++;
	envp_copy = (char **) malloc(sizeof(char *) * (i + 1 + extra_slot));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = 0;
	if (extra_slot)
		envp_copy[++i] = 0;
	return (envp_copy);
}

void	append_env(char *var_name, char *value, t_data *data)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = clone_env(data->envp, 1);
	while (new_envp && new_envp[i])
		i++;
	if (value)
		new_envp[i] = join_env_var_and_value(var_name, value);
	else
		new_envp[i] = ft_strdup(var_name);
	free_2d(data->envp);
	data->envp = new_envp;
	safe_free(var_name);
	safe_free(value);
}

void	modify_env(char *var_name, char *value, t_data *data)
{
	int	i;

	i = 0;
	if (!env_exists(var_name, data))
	{
		printf("Debug: Appending env variable.\n");
		append_env(var_name, value, data);
		return ;
	}
	printf("Debug: Modifying existing env variable.\n");
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], var_name, ft_counttochars(data->envp[i], '=', '\0')))
		{
			if (value)
			{
				safe_free(data->envp[i]);
				data->envp[i] = join_env_var_and_value(var_name, value);
			}
			break ;
		}
		i++;
	}
	safe_free(var_name);
	safe_free(value);
}

void	free_block(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_counttochars(envp[i], '=', '\0')))
		{
			safe_free(envp[i]);
			break ;
		}
		i++;
	}
}

void	delete_env(char *var_name, t_data *data)
{
	int		i;
	char	*tmp;
	int		env_count;
	char	**new_envp;

	i = 0;
	if (!env_exists(var_name, data))
		return ;
	env_count = ft_count2darr(data->envp);
	new_envp = (char **) malloc(sizeof(char *) * env_count);
	if (!new_envp)
		return ;
	new_envp[env_count] = 0;
	while (data->envp && i < env_count)
	{
		tmp = ft_substr(data->envp[i], 0, ft_counttochars(data->envp[i], '=', '\0'));
		if (ft_strcmp(var_name, tmp))
			new_envp[i] = ft_strdup(data->envp[i]);
		safe_free(tmp);
		i++;
	}
	free_2d(data->envp);
	data->envp = new_envp;
}
