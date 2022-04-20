/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:43:33 by imustafa          #+#    #+#             */
/*   Updated: 2021/09/28 15:18:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{	
	size_t	i;
	char	*a;

	i = 0;
	a = (char *) b;
	while (i < len)
	{
		a[i] = c;
		i++;
	}
	return (b);
}
