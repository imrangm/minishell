/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:54:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 17:00:35 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsep(const char *s1, const char *s2, char sep)
{
	char	*cs;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	cs = (char *) malloc(ft_strlen(s1) + ft_strlen (s2) + 2 * sizeof(char));
	i = 0;
	j = 0;
	if (!cs)
		return (0);
	while (s1[i] != '\0')
	{
		cs[i] = s1[i];
		i++;
	}
	cs[i] = sep;
	i++;
	while (s2[j] != '\0')
		cs[i++] = s2[j++];
	cs[i] = '\0';
	return (cs);
}
