/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:23:41 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/06 19:25:31 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	while (i < s1_len && i < s2_len)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i < s1_len || i < s2_len)
		return (1);
	return (0);
}
