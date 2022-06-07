/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/07 15:57:28 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_up_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	return (i);
}

char	*get_env_value(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strchr(envp[i], '='))
			return (ft_strdup(" "));
		if (!ft_strncmp(str, envp[i], count_up_to_equal(str))
			&& envp[i][ft_strlen(str)] == '=')
			return (ft_substr(ft_strchr(envp[i], '='),
					1, ft_strlen(ft_strchr(envp[i], '='))));
		i++;
	}
	return (NULL);
}

int	env_exists(char *var_name, char **envp)
{
	int		i;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name))
				&& envp[i][ft_strlen(var_name)] == '=')
				return (1);
		}
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name)))
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

char	**append_env(char *var_name, char *value, char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = clone_env(envp, 1);
	while (new_envp[i])
		i++;
	if (value)
		new_envp[i] = join_env_var_and_value(var_name, value);
	else
		new_envp[i] = ft_strdup(var_name);
	free_2d(envp);
	return (new_envp);
}

void	modify_env(char *var_name, char *value, char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_strlen(var_name)))
		{
			safe_free(envp[i]);
			if (!value)
				envp[i] = ft_strdup(var_name);
			else
				envp[i] = join_env_var_and_value(var_name, value);
			break ;
		}
		i++;
	}
}

int	count_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

void	free_block(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strcmp(envp[i], var_name))
		{
			safe_free(envp[i]);
			envp[i] = NULL;
			break ;
		}
		i++;
	}
}

void	delete_env(char *var_name, char **envp)
{
	int	i;
	int	env_count;

	i = 0;
	env_count = count_env(envp);
	if (!env_exists(var_name, envp))
		return ;
	if (env_count == 1)
	{
		safe_free(envp[0]);
		envp[0] = NULL;
		return ;
	}
	free_block(var_name, envp);
	while (envp && i + 1 < env_count)
	{
		safe_free(envp[i]);
		envp[i] = ft_strdup(envp[i + 1]);
		i++;
	}
	if (envp)
	{
		envp[i] = 0;
		envp[++i] = 0;
	}
}

char	**add_env(char *var_name, char *value, char **envp)
{
	char	**appended_env;

	appended_env = NULL;
	if (env_exists(var_name, envp))
	{
		if (value)
			modify_env(var_name, value, envp);
		safe_free(var_name);
		safe_free(value);
		return (envp);
	}
	appended_env = append_env(var_name, value, envp);
	safe_free(var_name);
	safe_free(value);
	return (appended_env);
}
