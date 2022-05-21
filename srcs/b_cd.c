/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/22 00:20:21 by nmadi            ###   ########.fr       */
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

static int	root_relative_chdir(char *new_path, t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		data->last_exit_status = 1;
		free(pwd);
		free(cwd);
		return (1);
	}
	else
		data->last_exit_status = 0;
	free(pwd);
	free(cwd);
	return (0);
}

static int	relative_chdir(char *new_path, char *pwd, t_data *data)
{
	char	*full_path;

	full_path = join_paths(new_path, pwd);
	if (chdir(full_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		data->last_exit_status = 1;
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

int	full_chdir(char *new_path, t_data *data)
{
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

int	b_cd(char **args, t_data *data)
{
	char	*cwd;
	char	*pwd;
	int		rv;

	cwd = NULL;
	rv = 0;
	if (invalid_args_count(args, data))
	{
		ft_free_arg(args);
		return (1);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (args[1][0] == '/' && pwd[0] == '/' && !pwd[1])
		rv = root_relative_chdir(args[1], data);
	else if (args[1][0] == '/')
		rv = full_chdir(args[1], data);
	else
		rv = relative_chdir(pwd, args[1], data);
	data->last_exit_status = 0;
	free(pwd);
	free(cwd);
	return (rv);
}
