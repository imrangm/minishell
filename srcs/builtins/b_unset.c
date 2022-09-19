/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:34:30 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/19 11:29:43 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	b_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "_", ft_counttochars(args[i], '=', '\0')))
		{
			if (env_exists(args[i], data))
				delete_env(args[i], data);
		}
		i++;
	}
}
