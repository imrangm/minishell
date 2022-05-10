/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/10 21:16:51 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Proprietary get_env()
*/
char	*get_env_value(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], ft_strlen(str))
			&& envp[i][ft_strlen(str)] == '=')
			return(ft_substr(ft_strchr(envp[i], '='),
					1, ft_strlen(ft_strchr(envp[i], '='))));
		i++;
	}
	return (NULL);
}

/*
* Returns 1 if env exists; otherwise returns 0.
*/
int	env_exists(char *var_name, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name))
			&& envp[i][ft_strlen(var_name)] == '=')
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
	while (envp[i])
		i++;
	envp_copy = (char **) malloc(sizeof(char *) * (i + 1 + extra_slot));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = (char *) malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(envp_copy[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envp_copy[i] = 0;
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
	new_envp[i] = join_env_var_and_value(var_name, value);
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
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
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_strlen(var_name)))
		{
			free(envp[i]);
			envp[i] = join_env_var_and_value(var_name, value);
			break ;
		}
		i++;
	}
}

//! For testing purposes
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	data.envp = clone_env(envp, 1);
	data.envp = append_env("Cat", "Potato", data.envp);
	modify_env("HOME", "/Rossiya", data.envp);
	modify_env("PATH", "Vjope:ya ne znayu:bla", data.envp);
	b_env(&data);
	int i = 0;
	while (data.envp[i])
	{
		free(data.envp[i]);
		i++;
	}
	free(data.envp);
	return (0);
}
