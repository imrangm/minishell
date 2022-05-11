/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:00:22 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/10 15:43:40 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], "<>") == 1
			&& char_is_separator(str[i], "<>") == 0)
			words++;
		if (char_is_separator(str[i + 1], "<>") == 0
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
	split[*word] = (char *) malloc (sizeof(char) * (j + 1));
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

char	**ft_split_rd(char *str)
{
	char	**res;
	int		words;

	words = count_words(str);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	res[words] = 0;
	write_split(res, str);
	return (res);
}