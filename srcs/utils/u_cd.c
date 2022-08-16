/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:42:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 18:09:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_full(char *new_path)
{
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd_relative(char *new_path, char *pwd)
{
	char	*full_path;

	full_path = ft_strsep(new_path, pwd, '/');
	if (chdir(full_path) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		safe_free(full_path);
		return (1);
	}
	safe_free(full_path);
	return (0);
}

int	cd_home(t_data *data)
{
	char	*destination;

	if (!env_exists("HOME", data))
	{
		ft_putstr_fd("Error: HOME not set\n", 2);
		return (1);
	}
	destination = get_env_value("HOME", data);
	if (chdir(destination) == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		safe_free(destination);
		return (1);
	}
	safe_free(destination);
	return (0);
}