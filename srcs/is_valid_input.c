/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:03:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/21 03:06:59 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_input(char *str)
{
	if (are_valid_backslashes(str, '\"') || are_valid_backslashes(str, '\''))
	{
		if (!are_valid_quotes(str))
			return (0);
	}
	else
	{
		ft_putstr_fd("Error: Backslashes are not permitted.\n", 2);
		return (0);
	}
	return (1);
}
