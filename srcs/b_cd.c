/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/20 13:50:47 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_paths(char *cwd, char *np)
{
	int		i;
	int		j;
	char	*a;

	a = (char *) malloc ((ft_strlen(cwd) + ft_strlen(np) + 2) * sizeof(char));
	i = 0;
	j = 0;
	if (a == NULL)
		return (NULL);
	while (cwd[i] != '\0')
	{
		a[i] = cwd[i];
		i++;
	}
	a[i] = '/';
	i++;
	while (np[j] != '\0')
		a[i++] = np[j++];
	a[i] = '\0';
	return (a);
}

static int	invalid_args_count(char **args, t_data *data)
{
	if (args[2])
	{
		ft_putstr_fd("Error: too many arguments.\n", 2);
		data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

static char	*smart_join_paths(char *new_path, char *pwd)
{
	if (pwd[0] == '/' && !pwd[2])
		return (ft_strjoin(pwd, new_path));
	else
		return (join_paths(pwd, new_path));
}

static int	root_or_dot_chdir(char *new_path, t_data *data)
{
	if (new_path[0] == '/' || new_path[0] == '.')
	{
		if (chdir(new_path) == -1)
		{
			ft_putstr_fd("Error: No such file or directory\n", 2);
			data->last_exit_status = 1;
			return (1);
		}
	}
	data->last_exit_status = 0;
	return (0);
}

static int	relative_chdir(char *new_path, t_data *data)
{
	char	*cwd;
	char	*pwd;
	char	*full_path;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	full_path = smart_join_paths(new_path, pwd);
	if (!full_path || !pwd)
		return (1);
	if (chdir(full_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		data->last_exit_status = 1;
		free(full_path);
		free(pwd);
		free(cwd);
		return (1);
	}
	free(full_path);
	free(pwd);
	free(cwd);
	data->last_exit_status = 0;
	return (0);
}

int	b_cd(char **args, t_data *data)
{
	if (invalid_args_count(args, data))
		return (1);
	else if (root_or_dot_chdir(args[1], data))
		return (1);
	else if (relative_chdir(args[1], data))
		return (1);
	return (0);
}
