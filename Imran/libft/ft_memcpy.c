/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:01:09 by imustafa          #+#    #+#             */
/*   Updated: 2021/09/30 12:32:37 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{	
	size_t	i;
	char	*a;
	char	*b;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	a = (char *) dst;
	b = (char *) src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
