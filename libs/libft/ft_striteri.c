/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:26:00 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 12:10:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int				i;
	unsigned int	j;

	if (!s || !f)
		return ;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		(*f)(j, &s[i]);
		i++;
		j++;
	}
}
