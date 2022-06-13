/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:34:30 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/13 18:27:52 by nmadi            ###   ########.fr       */
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
			delete_env(args[i], data);
		i++;
	}
}
