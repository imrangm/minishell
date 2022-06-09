/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:14:45 by nmadi             #+#    #+#             */
/*   Updated: 2021/10/03 02:19:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	l;
	size_t			i;
	char			*str;

	str = (char *) b;
	l = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		str[i] = l;
		i++;
	}
	return (str);
}
