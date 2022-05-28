/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:19:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/28 12:39:04 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_envp(char **envp)
{
	char	*cwd;
	char	**cloned_envp;

	cwd = NULL;
	cloned_envp = NULL;
	cloned_envp = clone_env(envp, 0);
	if (!cloned_envp[0])
	{
		cloned_envp = add_env("_", "/usr/bin/env", cloned_envp);
		cloned_envp = add_env("SHLVL", "1", cloned_envp);
	}
	else
		cloned_envp = add_env("_",
			ft_strjoin(getcwd(cwd, sizeof(cwd)), "minishell"), cloned_envp);
	cloned_envp = add_env("PWD",
			getcwd(cwd, sizeof(cwd)), cloned_envp);
	return (cloned_envp);
}
