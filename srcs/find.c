/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:06:27 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/22 11:39:05 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Splits the PATH variable by delimiter and returns paths
*/
char	**split_path(char *path)
{
	int		i;
	int		j;
	char	**paths;

	i = 0;
	j = 0;
	paths = ft_split_path(&path[5], ':');
	while (paths[i])
	{
		j = ft_strlen(paths[i]);
		paths[i][j] = '/';
		paths[i][j + 1] = '\0';
		i++;
	}
	return (paths);
}

/*
** checks if the command exists by going through different paths
** specified in the environment
*/
char	*find_exec(char *cmd, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!access(full_path, F_OK))
		{
			ft_free_arg(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_arg(paths);
	return (NULL);
}

char	*validate_cmd(char *cmd, char **args, t_data *data)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		data->last_exit_status = 127;
		ft_free_arg(args);
		return (NULL);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("Error: no permission to execute this command\n", 2);
		data->last_exit_status = 126;
		ft_free_arg(args);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

/*
** culmination of previous functions to return command path
*/
char	*get_cmd_path(char **args, t_data *data)
{
	char	*path_env_val;
	char	**paths;
	char	*cmd;

	if (ft_strchr(args[0], '/'))
		return (args[0]);
	path_env_val = get_env_value("PATH", data->envp);
	if (!path_env_val)
		return (NULL);
	paths = split_path(path_env_val);
	cmd = find_exec(args[0], paths);
	return (validate_cmd(cmd, args, data));
}