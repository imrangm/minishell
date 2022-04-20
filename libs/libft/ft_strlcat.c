/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:27:45 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/05 15:40:34 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize < dstlen + 1)
		return (dstsize + srclen);
	if (dstsize > dstlen + 1)
	{
		while (dstlen + i < dstsize - 1 && src[i] != '\0')
		{
			dst[dstlen + i] = src[i];
			i++;
		}	
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
