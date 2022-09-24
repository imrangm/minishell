/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:11:00 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_absolute(char *new_path)
{
	if (chdir(new_path))
	{
		ft_putendl_fd("Error: No such file or directory", 2);
		return (1);
	}
	return (0);
}

int	cd_relative(char *new_path, char *pwd)
{
	char	*full_path;

	full_path = ft_strsep(new_path, pwd, '/');
	if (chdir(full_path))
	{
		ft_putendl_fd("Error: No such file or directory", 2);
		ft_free(full_path);
		return (1);
	}
	ft_free(full_path);
	return (0);
}

int	cd_special(void)
{
	ft_putendl_fd("Error: getcwd() did not return a path", 2);
	return (cd_absolute("/"));
}

void	update_pwds(char *pwd, t_data *data)
{
	char	*rhs;

	rhs = NULL;
	if (data->last_exit_status)
	{
		ft_free(pwd);
		return ;
	}
	if (env_exists("OLDPWD", data))
	{
		if (env_exists("PWD", data))
			rhs = get_env_value("PWD", data);
		if (!rhs)
			modify_env(ft_strdup("OLDPWD"), ft_strdup(pwd), data);
		else
			modify_env(ft_strdup("OLDPWD"), rhs, data);
	}
	if (env_exists("PWD", data))
		modify_env(ft_strdup("PWD"), getcwd(NULL, 0), data);
	ft_free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	ft_free(pwd);
}

int	b_cd(char **args, t_data *data)
{
	char	*pwd;

	if (ft_count2darr(args) > 2)
	{
		data->last_exit_status = 0;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		data->last_exit_status = cd_special();
	else if ((args[1][0] == '/' && pwd[0] == '/' && !pwd[1])
		|| args[1][0] == '/')
		data->last_exit_status = cd_absolute(args[1]);
	else
		data->last_exit_status = cd_relative(pwd, args[1]);
	update_pwds(pwd, data);
	return (data->last_exit_status);
}
