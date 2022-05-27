/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:34:30 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/27 14:36:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	b_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env(args[i], data->envp);
		i++;
	}
}
