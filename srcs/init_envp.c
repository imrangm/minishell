/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:19:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/26 17:38:14 by nmadi            ###   ########.fr       */
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
	cloned_envp = add_env(ft_strdup("PWD"), getcwd(cwd, sizeof(cwd)), cloned_envp);
	return (cloned_envp);
}
