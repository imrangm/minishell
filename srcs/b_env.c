/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:19:34 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 23:25:34 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_env(char **envp, int export_mode)
{
	int	i;

	i = 0;
	while (envp[i]) //! Check if a variable has no equal sign. Do not print it
	{
		if (!ft_strchr(envp[i], '=') && export_mode)
			printf("declare -x %s\n", envp[i]);
		else if (ft_strchr(envp[i], '=') && export_mode)
			printf("declare -x %s\n", envp[i]);
		else if (ft_strchr(envp[i], '=') && !export_mode)
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
