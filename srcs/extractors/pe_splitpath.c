/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_splitpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:42:57 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			split[word] = (char *) malloc (sizeof(char) * (j + 2));
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
}

char	**pe_split_path(char *s, char c)
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
