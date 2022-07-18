/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_splitrd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:00:22 by imustafa          #+#    #+#             */
/*   Updated: 2022/07/18 07:55:19 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	char_is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(char *str)
{
	int	i;
	int	q;
	int	words;

	words = 0;
	q = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_setquote(str[i], &q))
			i++;
		if (str[i] && !q && char_is_separator(str[i + 1], "<>") == 1
			&& char_is_separator(str[i], "<>") == 0)
			words++;
		if (str[i] && !q && char_is_separator(str[i + 1], "<>") == 0
			&& char_is_separator(str[i], "<>") == 1)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, char *from, int rd)
{
	int	i;

	i = 0;
	while (char_is_separator(from[i], "<>") == rd)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	new_word(char **split, char *str, int *pos, int *word)
{
	int	j;

	j = 0;
	while (char_is_separator(str[*pos + j], "<>") == 0)
		j++;
	split[*word] = (char *) malloc(sizeof(char) * (j + 1));
	write_word(split[*word], str + (*pos), 0);
	*pos += j;
	(*word)++;
}

static void	write_split(char **split, char *str)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], "<>") == 1)
		{
			j = 0;
			while (char_is_separator(str[i + j], "<>") == 1)
				j++;
			split[word] = (char *) malloc (sizeof(char) * (j + 1));
			write_word(split[word], str + i, 1);
			i += j;
			word++;
		}
		else
			new_word(split, str, &i, &word);
	}
}

char	**split_rd(char *str)
{
	char	**res;
	int		words;
	char	**trim;
	int		i;

	words = count_words(str);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	res[words] = 0;
	if (!res)
		return (NULL);
	write_split(res, str);
	trim = (char **)malloc(sizeof(char *) * (words + 1));
	if (!trim)
		return (NULL);
	trim[words] = 0;
	i = 0;
	while (res[i])
	{
		trim[i] = ft_strtrim(res[i], " ");
		free(res[i]);
		i++;
	}
	free(res);
	return (trim);
}
