/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 04:14:04 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/23 05:02:32 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	count_elements(char *str)
{
	int	i;
	int	ec;

	i = 0;
	ec = 0;
	while (str[i] && str[i] == 32)
		i++;
	if (str[i] != 32)
		ec++;
	while (str[i])
	{
		if (str[i] == 32)
		{
			if (str[i + 1] != 32 && str[i + 1] != 0)
				ec++;
		}
		i++;
	}
	return (ec);
}

// static void	write_word(char *dest, const char *from, char charset)
// {
// 	int	i;

// 	i = 0;
// 	while (separator(from[i], charset) == 0)
// 	{
// 		dest[i] = from[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// }

// static void	write_split(char **split, const char *str, char charset)
// {
// 	int		i;
// 	int		j;
// 	int		word;

// 	word = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (separator(str[i], charset) == 1)
// 			i++;
// 		else
// 		{
// 			j = 0;
// 			while (separator(str[i + j], charset) == 0)
// 				j++;
// 			split[word] = (char *) malloc (sizeof(char) * (j + 2));
// 			write_word(split[word], str + i, charset);
// 			i += j;
// 			word++;
// 		}
// 	}
// }

char	**ft_split_line(char *str)
{
	// char	**res;
	int		elements_count;

	elements_count = count_elements(str);
	printf("ec = %d\n", elements_count);
	// res = (char **) malloc (sizeof(char *) * (elements_count + 1));
	// if (res == NULL)
	// 	return (NULL);
	// res[elements_count] = 0;
	// write_split(res, s, c);
	// return (res);
	return (NULL);
}
