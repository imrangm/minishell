/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 17:17:21 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	update_env_access(t_data *data)
// {
// 	ft_putstr_fd("Error: cannot access parent directories. ", 2);
// 	ft_putstr_fd("Redirecting to root regardless of input.\n", 1);
// 	chdir("/");
// 	safe_free(data->old_pwd);
// 	if (data->pwd)
// 		data->old_pwd = ft_strdup(data->pwd);
// 	modify_env(ft_strdup("OLDPWD"), data->old_pwd, data);
// 	safe_free(data->pwd);
// 	data->pwd = ft_strdup("/");
// 	modify_env(ft_strdup("PWD"), ft_strdup("/"), data);
// 	data->last_exit_status = 0;
// }

// static int	handle_del_dir(t_data *data)
// {
// 	char	*pwd;
// 	char	*old_pwd;

// 	pwd = NULL;
// 	old_pwd = NULL;
// 	if (data->old_pwd != NULL && chdir(data->old_pwd) != -1)
// 	{
// 		pwd = ft_strdup(data->pwd);
// 		old_pwd = ft_strdup(data->old_pwd);
// 		safe_free(data->pwd);
// 		safe_free(data->old_pwd);
// 		data->pwd = ft_strdup(old_pwd);
// 		data->old_pwd = ft_strdup(pwd);
// 	}
// 	else
// 		update_env_access(data);
// 	return (0);
// }

int	b_cd(char **args, t_data *data)
{
	char	*pwd;

	if (ft_count2darr(args) > 2)
	{
		data->last_exit_status = 0;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	printf("pwd = %s\n", pwd);

	// if (!pwd) //! Handles if you are in a deleted working dir
	// 	return (handle_del_dir(data));
	// if (ft_count2darr(args) == 1) //! Handles cd to home
	// 	return (cd_home(data));
	if ((args[1][0] == '/' && pwd[0] == '/' && !pwd[1]) || args[1][0] == '/')
		data->last_exit_status = cd_full(args[1]);
	else
		data->last_exit_status = cd_relative(pwd, args[1]);
	// update_pwd_oldpwd(pwd, data->last_exit_status, data); //! Reimplement with env

	//! Three lines are for testing purposes
	safe_free(pwd);
	pwd = getcwd(NULL, 0);
	printf("pwd now = %s\n", pwd);

	safe_free(pwd);
	return (data->last_exit_status);
}
