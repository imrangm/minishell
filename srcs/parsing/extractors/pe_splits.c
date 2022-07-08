/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/08 17:50:58 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_element_count(char *str)
{
	int	i;
	int	quote;
	int	element_count;

	i = 0;
	quote = 0;
	element_count = 0;
	if (!ft_isspace(str[0]))
		element_count++;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (!quote && ft_isspace(str[i]) && str[i + 1]
			&& !ft_isspace(str[i + 1]))
			element_count++;
		i++;
	}
	return (element_count);
}

static int	is_space_out_quotes(char c, int *quote)
{
	if (ft_isspace(c) && !(*quote))
		return (1);
	return (0);
}

static int	get_next_word_len(char *str)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !is_space_out_quotes(str[i], &quote))
	{
		ft_setquote(str[i], &quote);
		len++;
		i++;
	}
	// printf("word in gnw_len = |%s|\n", str);
	// printf("%d\n", len);
	return (len);
}

static char	**get_elements(char *str, char **elements, int element_count)
{
	int		i;
	int		j;
	int		s;
	char	*tmp;
	int		element_size;

	i = 0;
	j = 0;
	s = 0;
	element_size = 0;
	while (i < element_count)
	{
		element_size = get_next_word_len(str);
		j = ft_skipspaces(str);
		// printf("j = %d | element size - j = %d\n", j, element_size - j);
		elements[i] = ft_substr(str, j, element_size);
		s = j + element_size + 1;
		tmp = ft_substr(str, s, (ft_strlen(str) - element_size) + 1);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (elements);
}

char	**smart_split(char *str)
{
	int		element_count;
	char	**elements;
	char	**stripped_elements;

	element_count = get_element_count(str);
	elements = malloc(sizeof(char *) * (element_count + 1));
	elements[element_count] = 0;
	elements = get_elements(str, elements, element_count);
	// Expand here
	stripped_elements = strip_quotes(elements, element_count);
	// printf("\n\n---[Elements %d]---\n\n", element_count);
	// for (int i = 0; stripped_elements[i]; i++) //! Remember to remove.
	// 	printf("Element %i = |%s|\n", i, stripped_elements[i]);
	// printf("\n---[Elements]---\n\n");
	return (stripped_elements);
}
