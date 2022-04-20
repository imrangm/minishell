/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_valid_backslashes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:20:55 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/21 03:08:20 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	are_valid_backslashes(char *str, char quote)
{
	int	i;
	int	quote_mode;

	i = 0;
	quote_mode = 0;
	while (str[i])
	{
		if (str[i] == quote && !quote_mode)
			quote_mode = 1;
		else if (str[i] == quote && quote_mode)
			quote_mode = 0;
		if (str[i] == '\\' && !quote_mode)
			return (0);
		i++;
	}
	return (1);
}
