/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:04:11 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/03 16:35:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;
	int				count;

	i = 0;
	count = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	if (n == 0 || (a == 0 && b == 0))
		return (0);
	while (i < n && (a[i] != '\0' || b[i] != '\0'))
	{
		if (a[i] != b[i])
		{
			count += a[i] - b[i];
			break ;
		}
		i++;
	}
	return (count);
}
