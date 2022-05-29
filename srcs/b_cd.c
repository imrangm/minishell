/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/29 13:11:10 by nmadi            ###   ########.fr       */
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

static int	handle_del_dir(t_data *data)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	if (chdir(get_env_value("OLDPWD", data->envp)) != -1)
	{
		pwd = ft_strdup(data->pwd);
		old_pwd = ft_strdup(data->old_pwd);
		free(data->pwd);
		free(data->old_pwd);
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
	printf("1\n");
	if (invalid_args_count(args, data))
	{
		printf("2\n");
		ft_free_arg(args);
		return (1);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd) // This is when you are in a deleted dir. Consider adding another arg to loop it and turn it into a whileeee
		return (handle_del_dir(data));
	if (args[1][0] == '/' && pwd[0] == '/' && !pwd[1])
		rv = root_relative_chdir(args[1]);
	else if (args[1][0] == '/')
		rv = full_chdir(args[1]);
	else
		rv = relative_chdir(pwd, args[1]);
	printf("4\n");
	data->last_exit_status = rv;
	update_env(pwd, rv, data);
	printf("5\n");
	free(pwd);
	free(cwd);
	return (rv);
}
