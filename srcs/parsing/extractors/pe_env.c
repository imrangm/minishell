/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:19:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/13 18:23:35 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	set_shlvl(t_data *data)
{
	int		shlvl;
	char	*shlvl_rhs;

	shlvl = 0;
	shlvl_rhs = NULL;
	if (env_exists("SHLVL", data))
	{
		shlvl_rhs = get_env_value("SHLVL", data);
		shlvl = ft_atoi(shlvl_rhs) + 1;
		modify_env("SHLVL", ft_itoa(shlvl), data);
	}
}

void	init_envp(char **envp, t_data *data)
{
	char	*cwd;

	cwd = NULL;
	data->envp = clone_env(envp, 0);
	delete_env("OLDPWD", data);
	modify_env("OLDPWD", NULL, data);
	if (!data->envp[0])
	{
		modify_env("SHLVL", "1", data);
		if (!env_exists("_", data))
			modify_env("_", "/usr/bin/env", data);
	}
	else
	{
		modify_env("_", ft_strjoin(getcwd(cwd, sizeof(cwd)), "/minishell"), data);
		set_shlvl(data);
	}
	modify_env("PWD", getcwd(cwd, sizeof(cwd)), data);
}
