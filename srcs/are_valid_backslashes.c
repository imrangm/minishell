/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_valid_backslashes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:20:55 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/22 02:47:48 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	are_valid_backslashes(char *str)
{
	int	i;
	int	s_quote_mode;
	int	d_quote_mode;

	i = 0;
	s_quote_mode = 0;
	d_quote_mode = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !s_quote_mode)
			s_quote_mode = 1;
		else if (str[i] == '\'' && s_quote_mode)
			s_quote_mode = 0;
		else if (str[i] == '\"' && !d_quote_mode)
			d_quote_mode = 1;
		else if (str[i] == '\"' && d_quote_mode)
			d_quote_mode = 0;
		if (str[i] == '\\' && !s_quote_mode && !d_quote_mode && are_valid_quotes(str))
			return (0);
		i++;
	}
	return (1);
}
