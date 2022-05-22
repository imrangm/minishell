/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/22 15:43:13 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_up_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
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
		if (!ft_strncmp(str, envp[i], count_up_to_equal(str)) && envp[i][ft_strlen(str)] == '=')
			return(ft_substr(ft_strchr(envp[i], '='), 1, ft_strlen(ft_strchr(envp[i], '='))));
		i++;
	}
	return (NULL);
}

int	env_exists(char *var_name, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name))
				&& envp[i][ft_strlen(var_name)] == '=')
				return(1);
		}
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name)))
			return(1);
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

	i = 0;
	if (!envp[0])
		return (NULL);
	while (envp[i])
		i++;
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
	ft_free_arg(envp);
	return (new_envp);
}

void	modify_env(char *var_name, char *value, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_strlen(var_name)))
		{
			free(envp[i]);
			if (!value)
				envp[i] = ft_strdup(var_name);
			else
				envp[i] = join_env_var_and_value(var_name, value);
			break ;
		}
		i++;
	}
}

void	unset_env(char *var_name, char **envp)
{
	int	i;

	i = 0;
	if (!env_exists(var_name, envp))
		return ;
	while (envp[i])
	{
		if (!cmp_str(envp[i], var_name))
		{
			free(envp[i]);
			envp[i] = NULL;
			break ;
		}
		i++;
	}
	while (envp[i + 1])
	{
		free(envp[i]);
		envp[i] = NULL;
		envp[i] = (char *) malloc(sizeof(char) * (ft_strlen(envp[i + 1]) + 1));
		ft_strlcpy(envp[i], envp[i + 1], ft_strlen(envp[i + 1]) + 1);
		i++;
	}
	envp[i] = 0;
	envp[++i] = 0;
}

char	**add_env(char *var_name, char *value, char **envp)
{
	char	**appended_env;

	appended_env = NULL;
	if (env_exists(var_name, envp))
	{
		modify_env(var_name, value, envp);
		free(var_name);
		free(value);
		return (envp);
	}
	appended_env = append_env(var_name, value, envp);
	free(var_name);
	free(value);
	return (appended_env);
}
