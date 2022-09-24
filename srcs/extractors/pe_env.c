/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:10:05 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:10:06 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		modify_env(ft_strdup("SHLVL"), ft_strdup("1"), data);
	ft_free(shlvl_rhs);
}

void	init_envp(char **envp, t_data *data)
{
	data->pwd = NULL;
	data->envp = clone_env(envp, 0);
	if (env_exists("OLDPWD", data))
		delete_env("OLDPWD", data);
	set_shlvl(data);
	modify_env(ft_strdup("OLDPWD"), NULL, data);
	modify_env(ft_strdup("PWD"), getcwd(NULL, 0), data);
}
