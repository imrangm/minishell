/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:43:06 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 11:14:24 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*a;

	if (!s1 || !s2)
		return (NULL);
	a = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (a == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		a[i++] = s2[j++];
	a[i] = '\0';
	return (a);
}
