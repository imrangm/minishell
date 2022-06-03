/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:19:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/03 18:14:58 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**set_shlvl(char **cloned_envp)
{
	int		shlvl;
	char	*shlvl_rhs;

	shlvl = 0;
	shlvl_rhs = NULL;
	if (env_exists("SHLVL", cloned_envp))
	{
		shlvl_rhs = get_env_value("SHLVL", cloned_envp);
		shlvl = ft_atoi(shlvl_rhs) + 1;
		cloned_envp = add_env("SHLVL", ft_itoa(shlvl), cloned_envp);
	}
	return (cloned_envp);
}

char	**init_envp(char **envp)
{
	char	*cwd;
	char	**cloned_envp;

	cwd = NULL;
	cloned_envp = NULL;
	cloned_envp = clone_env(envp, 0);
	if (!cloned_envp[0])
	{
		cloned_envp = add_env("SHLVL", "1", cloned_envp);
		if (!env_exists("_", cloned_envp))
			cloned_envp = add_env("_", "/usr/bin/env", cloned_envp);
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		cloned_envp = add_env("_",
				ft_strjoin(cwd, "minishell"), cloned_envp); //! Yields _=./minishell instead of the full path to minishell.
		cloned_envp = set_shlvl(cloned_envp);
	}
	cloned_envp = add_env("PWD",
			getcwd(cwd, sizeof(cwd)), cloned_envp);
	return (cloned_envp);
}
