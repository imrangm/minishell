/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:06:27 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/22 00:09:21 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Splits the PATH variable by delimiter and returns paths
*/
char	**split_path(char *path)
{
	char	**strs;
	char	*newpath;
	int		fwd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fwd = 5;
	newpath = &path[fwd];
	strs = ft_split_path(newpath, ':');
	while (strs[i])
	{
		j = ft_strlen(strs[i]);
		strs[i][j] = '/';
		strs[i][j + 1] = '\0';
		i++;
	}
	return (strs);
}

/*
** checks if the command exists by going through different paths
** specified in the environment
*/
char	*find_exec(char *prg, char	**paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], prg);
		if (access(full_path, X_OK) == 0)
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

/*
** culmination of previous functions to return command path
*/
char	*get_cmd_path(char **args, t_data *data)
{
	char	*path_env_val;
	char	**paths;
	char	*cmd_path;

	if (ft_strchr(args[0], '/'))
		return (args[0]);
	path_env_val = get_env_value("PATH", data->envp);
	if (!path_env_val)
		return (NULL);
	paths = split_path(path_env_val);
	cmd_path = find_exec(args[0], paths);
	if (!cmd_path)
	{
		if (access(cmd_path, F_OK) == -1)
		{
			ft_putstr_fd("Error: command not found\n", 2);
			data->last_exit_status = 127;
			ft_free_arg(args);
			exit(data->last_exit_status);
		}
		else if (access(cmd_path, X_OK) == -1)
		{
			ft_putstr_fd("Error: no permission to execute command\n", 2);
			data->last_exit_status = 126;
			ft_free_arg(args);
			exit(data->last_exit_status);
		}
	}
	return (cmd_path);
}