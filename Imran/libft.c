/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:01:44 by imran             #+#    #+#             */
/*   Updated: 2022/04/08 17:11:13 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	separator(char c, char charset)
{
	if (c == charset)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(const char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (separator(str[i + 1], charset) == 1
			&& separator(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, const char *from, char charset)
{
	int	i;

	i = 0;
	while (separator(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	write_split(char **split, const char *str, char charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (separator(str[i + j], charset) == 0)
				j++;
			split[word] = (char *) malloc (sizeof(char) * (j + 1));
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **) malloc (sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	res[words] = 0;
	write_split(res, s, c);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*a;

	if (!s1 || !s2)
		return (NULL);
	a = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (a == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		a[i++] = s2[j++];
	a[i] = '\0';
	return (a);
}
