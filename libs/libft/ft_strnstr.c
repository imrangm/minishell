/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:29:36 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/04 16:40:43 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*a;

	a = (char *) haystack;
	j = 0;
	k = ft_strlen(needle);
	if (k == 0)
		return (a);
	while (a[j] != '\0' && len >= k)
	{
		i = 0;
		while (a[j + i] == needle[i] && a[j + i] != '\0' && needle[i] != '\0')
			i++;
		if (needle[i] == '\0')
			return (&a[j]);
		j++;
		len--;
	}
	return (NULL);
}
