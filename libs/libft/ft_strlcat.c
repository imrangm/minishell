/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 01:43:11 by nmadi             #+#    #+#             */
/*   Updated: 2021/10/08 01:44:18 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dl;
	size_t		sl;
	size_t		tot;
	size_t		i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	tot = sl + dl;
	i = 0;
	if (dl >= dstsize)
		return (sl + dstsize);
	while (src[i] != '\0' && dstsize - dl - 1)
	{
		dst[dl] = src[i];
		dl++;
		i++;
	}
	dst[dl] = '\0';
	return (tot);
}
