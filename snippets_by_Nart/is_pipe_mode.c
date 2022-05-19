/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:41:04 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/18 12:58:09 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! Be sure to change the includes
#include <stdio.h>

static int	set_quote_mode(char c, int *quote) //! Must be appended to our header
{
	if ((c == '\'' || c == '\"') && !(*quote))
	{
		(*quote) = c;
		return (1);
	}
	else if (c == (char) *quote && *quote)
	{
		(*quote) = 0;
		return (1);
	}
	return (0);
}

int	is_pipe_mode(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (set_quote_mode(str[i], &quote))
			i++;
		if (str[i] == '|' && !quote)
			return (1);
		i++;
	}
	return (0);
}
