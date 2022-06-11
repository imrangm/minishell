/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/11 18:15:27 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_env(char *old_pwd, int rv, t_data *data)
{
	char	*cwd;
	char	*pwd;

	if (rv)
		return ;
	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	safe_free(data->pwd);
	safe_free(data->old_pwd);
	data->pwd = ft_strdup(pwd);
	data->old_pwd = ft_strdup(old_pwd);
	modify_env("PWD", data->pwd, data);
	modify_env("OLDPWD", data->old_pwd, data);
	safe_free(cwd);
	safe_free(pwd);
}

static int	handle_del_dir(t_data *data)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	if (chdir(get_env_value("OLDPWD", data)) != -1)
	{
		pwd = ft_strdup(data->pwd);
		old_pwd = ft_strdup(data->old_pwd);
		safe_free(data->pwd);
		safe_free(data->old_pwd);
		data->pwd = ft_strdup(old_pwd);
		data->old_pwd = ft_strdup(pwd);
		return (99);
	}
	return (1);
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
		free_2d(args);
		return (1);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (handle_del_dir(data));
	if (args[1][0] == '/' && pwd[0] == '/' && !pwd[1])
		rv = root_relative_chdir(args[1]);
	else if (args[1][0] == '/')
		rv = full_chdir(args[1]);
	else
		rv = relative_chdir(pwd, args[1]);
	data->last_exit_status = rv;
	update_env(pwd, rv, data);
	safe_free(pwd);
	safe_free(cwd);
	return (rv);
}
