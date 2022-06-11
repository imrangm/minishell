/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:06:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/11 17:14:55 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_setquote(char c, int *quote)
{
	if (ft_isquote(c) && !(*quote))
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
