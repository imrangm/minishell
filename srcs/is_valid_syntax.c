/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 04:02:37 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/23 04:06:44 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_syntax(char *str)
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
		else if (str[i] == '\\' && !s_quote_mode && !d_quote_mode)
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
