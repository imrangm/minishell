/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:06:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/07 16:00:49 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_quote_mode(char c, int *quote)
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
