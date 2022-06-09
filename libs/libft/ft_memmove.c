/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 03:57:37 by nmadi             #+#    #+#             */
/*   Updated: 2021/10/04 01:39:31 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*destination;
	size_t	i;

	source = (char *) src;
	destination = (char *) dst;
	i = __UINT64_MAX__;
	if (!source && !destination)
		return (NULL);
	else if (source == destination)
		return (dst);
	else if (source < destination)
	{
		while (--len != __UINT64_MAX__)
			destination[len] = source[len];
		return (dst);
	}
	else if (source > destination)
	{
		while (++i < len)
			destination[i] = source[i];
		return (dst);
	}
	return (dst);
}
