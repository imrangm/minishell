/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:42:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/02 14:46:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_paths(char *cwd, char *np)
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

int	invalid_args_count(char **args, t_data *data)
{
	int	args_count;

	args_count = ft_count2darr(args);
	if (args_count > 2)
	{
		ft_putstr_fd("Error: too many arguments.\n", 2);
		data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

int	root_relative_chdir(char *new_path)
{
	char	*cwd;
	char	*pwd;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		free(pwd);
		free(cwd);
		return (1);
	}
	free(pwd);
	free(cwd);
	return (0);
}

int	relative_chdir(char *new_path, char *pwd)
{
	char	*full_path;

	full_path = join_paths(new_path, pwd);
	if (chdir(full_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

int	full_chdir(char *new_path)
{
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
