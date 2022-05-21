/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:19:34 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/21 18:08:36 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_env(char **envp, int export_mode)
{
	int		i;
	char	*side;

	i = 0;
	side = NULL;
	while (envp[i])
	{
		if (!ft_strchr(envp[i], '=') && export_mode)
			printf("declare -x %s\n", envp[i]);
		else if (ft_strchr(envp[i], '=') && export_mode)
		{
			side = get_export_value_side(envp[i], 1);
			printf("declare -x %s=", side);
			free(side);
			side = get_export_value_side(envp[i], 0);
			printf("\"%s\"\n", side);
			free(side);
		}
		else if (ft_strchr(envp[i], '=') && !export_mode)
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
