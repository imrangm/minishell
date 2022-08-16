/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:19:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 18:27:47 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	set_shlvl(t_data *data)
{
	int		shlvl;
	char	*shlvl_rhs;
	char	*shlvl_itoa;

	shlvl = 0;
	shlvl_rhs = NULL;
	shlvl_itoa = NULL;
	if (env_exists("SHLVL", data))
	{
		shlvl_rhs = get_env_value("SHLVL", data);
		if (!ft_aredigits(shlvl_rhs))
			modify_env(ft_strdup("SHLVL"), "1", data);
		else
		{
			shlvl = ft_atoi(shlvl_rhs) + 1;
			shlvl_itoa = ft_itoa(shlvl);
			modify_env(ft_strdup("SHLVL"), shlvl_itoa, data);
		}
	}
	else
		modify_env(ft_strdup("SHLVL"), "1", data);
	ft_free(shlvl_rhs);
}

void	init_envp(char **envp, t_data *data)
{
	char	*cwd;

	cwd = NULL;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->envp = clone_env(envp, 0);
	delete_env("OLDPWD", data);
	if (!data->envp[0])
	{
		modify_env(ft_strdup("OLDPWD"), NULL, data);
		modify_env(ft_strdup("SHLVL"), "1", data);
		if (!env_exists("_", data))
			modify_env("_", "/usr/bin/env", data);
	}
	else
	{
		append_env(ft_strdup("OLDPWD"), NULL, data);
		set_shlvl(data);
	}
	modify_env(ft_strdup("PWD"), getcwd(cwd, sizeof(cwd)), data);
}
