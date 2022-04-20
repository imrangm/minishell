/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:25:07 by imustafa          #+#    #+#             */
/*   Updated: 2021/09/28 18:05:46 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*a;

	a = (char *) s;
	i = 0;
	while (i < n)
	{
		if (a[i] == (char) c)
			return (a + i);
		i++;
	}
	return (NULL);
}
