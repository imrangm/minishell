/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:10:57 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/07 18:17:53 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "nart.h"

// static	int	get_elements_count(const char *s)
// {
// 	int		i;
// 	int		elements_count;

// 	i = 0;
// 	elements_count = 0;
// 	if (s[0] != 32)
// 		elements_count++;
// 	while (s[i])
// 	{
// 		if (s[i] == 32)
// 		{
// 			if (s[i + 1] != c && s[i + 1] != 0)
// 				elements_count++;
// 		}
// 		i++;
// 	}
// 	return (elements_count);
// }

// static	char	**ft_strcopy(char const *src, char c, char **dst, int i)
// {
// 	int		start;
// 	int		end;
// 	int		j;

// 	start = 0;
// 	end = 0;
// 	j = 0;
// 	while (src[i])
// 	{
// 		start = 0;
// 		if (src[i] != c)
// 		{
// 			start = i;
// 			while (src[i] != c && src[i])
// 				i++;
// 			end = i;
// 			dst[j] = ft_substr(src, start, end - start);
// 			j++;
// 		}
// 		else
// 			i++;
// 	}
// 	dst[j] = 0;
// 	return (dst);
// }

// char	**parse(char *str)
// {
// 	int		i;
// 	char	**new_str;

// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	str = (char **) malloc((get_elements_count(new_str) + 1) * sizeof(char *));
// 	if (!str)
// 		return (NULL);
// 	return (ft_strcopy(new_str, str, i));
// }
