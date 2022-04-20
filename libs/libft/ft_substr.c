/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:34:59 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 12:19:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
	{
		a = malloc(sizeof(char) * 1);
		if (a == NULL)
			return (NULL);
		a[0] = '\0';
		return (a);
	}
	a = (char *) malloc ((len + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
		a[i++] = s[start++];
	a[i] = '\0';
	return (a);
}
