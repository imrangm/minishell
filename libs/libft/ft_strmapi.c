/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:19:41 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 11:30:14 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	j;
	int				len;
	char			*a;

	if (!s || !f)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s);
	a = (char *) malloc ((len + 1) * sizeof (char));
	if (s == NULL || a == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		a[i] = (*f)(j, s[i]);
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}
