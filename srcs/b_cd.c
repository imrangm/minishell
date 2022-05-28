/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/28 12:32:37 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_env(char *old_pwd, int rv, t_data *data)
{
	char	*cwd;
	char	*pwd;

	if (rv)
		return ;
	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	ft_free(data->pwd);
	ft_free(data->old_pwd);
	data->pwd = ft_strdup(pwd);
	data->old_pwd = ft_strdup(old_pwd);
	ft_free(cwd);
	ft_free(pwd);
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
		rv = root_relative_chdir(args[1]);
	else if (args[1][0] == '/')
		rv = full_chdir(args[1]);
	else
		rv = relative_chdir(pwd, args[1]);
	data->last_exit_status = rv;
	update_env(pwd, rv, data);
	free(pwd);
	free(cwd);
	return (rv);
}
