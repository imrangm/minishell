/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:04:40 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 11:39:37 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (ft_strchr(set, (int) s1[i]))
			i++;
		else
			break ;
	}
	while (s1[len])
	{
		if (ft_strchr(set, (int) s1[len]) && i < len)
			len--;
		else
			break ;
	}
	return (ft_substr(s1, i, len - i + 1));
}
