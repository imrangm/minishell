/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 02:59:52 by nmadi             #+#    #+#             */
/*   Updated: 2021/10/06 03:39:40 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cs;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	cs = (char *) malloc(ft_strlen(s1) + ft_strlen (s2) + 1 * sizeof(*cs));
	i = 0;
	j = 0;
	if (!cs)
		return (0);
	while (s1[i] != '\0')
	{
		cs[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		cs[i] = s2[j];
		j++;
		i++;
	}
	cs[i] = '\0';
	return (cs);
}
