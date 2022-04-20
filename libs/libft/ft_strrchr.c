/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:29:24 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/03 15:55:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*f;

	i = ft_strlen(s);
	while (s[i] != (char) c)
	{
		if (i == 0 || s == 0)
			return (NULL);
		i--;
	}
	f = (char *) s + i;
	return (f);
}
