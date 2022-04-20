/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_backslashes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:20:55 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/21 02:36:52 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_backslashes(char *str)
{
	int	i;
	int	db_quote_mode;

	i = 0;
	db_quote_mode = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !db_quote_mode)
			db_quote_mode = 1;
		else if (str[i] == '\"' && db_quote_mode)
			db_quote_mode = 0;
		if (str[i] == '\\' && !db_quote_mode)
		{
			ft_putstr_fd("Error: Backslashes are not permitted.\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
