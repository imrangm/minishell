/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:06:27 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/21 18:47:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** returns the PATH variable from the environment
*/
char	*get_path(t_data *data)
{
	int					i;
	unsigned long		j;
	char				*find;

	i = 0;
	j = 0;
	find = "PATH=";
	while (data->envp[i])
	{
		j = 0;
		while (data->envp[i][j] == find[j])
		{
			if (j == ft_strlen(find) - 1)
				return (data->envp[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

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
	char	*find;

	i = 0;
	while (paths[i])
	{
		find = ft_strjoin(paths[i], prg);
		if (access(find, X_OK) == 0)
		{
			ft_free_arg(paths);
			return (find);
		}
		free(find);
		i++;
	}
	ft_free_arg(paths);
	return (NULL);
}

/*
** culmination of previous functions to return command path
*/
char	*cmd_path(char **args, t_data *data)
{
	char	*path_env_val;
	char	**paths;
	char	*output;

	if (ft_strchr(args[0], '/'))
		return (args[0]);
	path_env_val = get_path(data);
	if (!path_env_val)
		return (NULL);
	paths = split_path(path_env_val);
	output = find_exec(args[0], paths);
	if (!output)
	{
		perror("command not found");
		data->last_exit_status = 127;
		ft_free_arg(args);
		exit(127);
	}
	return (output);
}