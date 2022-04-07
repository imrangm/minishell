/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:23:54 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/07 18:13:23 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_element_counter(const char *s, char c)
{
	int		i;
	int		nw;

	i = 0;
	nw = 0;
	if (s[0] != c)
		nw++;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != 0)
				nw++;
		}
		i++;
	}
	return (nw);
}

static	char	**ft_strcopy(char const *src, char c, char **dst, int i)
{
	int		start;
	int		end;
	int		j;

	start = 0;
	end = 0;
	j = 0;
	while (src[i])
	{
		start = 0;
		if (src[i] != c)
		{
			start = i;
			while (src[i] != c && src[i])
				i++;
			end = i;
			dst[j] = ft_substr(src, start, end - start);
			j++;
		}
		else
			i++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;

	if (!s)
		return (0);
	i = 0;
	str = (char **) ft_calloc(ft_element_counter(s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	return (ft_strcopy(s, c, str, i));
}
