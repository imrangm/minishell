/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/04 00:24:51 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_element_count(char *str)
{
	int	i;
	int	quote;
	int	element_count;

	i = 0;
	quote = 0;
	element_count = 0;
	if (!is_space(str[0]))
		element_count++;
	while (str[i])
	{
		if (is_quote(str[i]) && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (!quote && is_space(str[i]) && str[i + 1] && !is_space(str[i + 1]))
		{
			if (!str[i + 2])
				element_count++;
			else if (!(str[i + 1] == SQUOTE && str[i + 2] == SQUOTE)
				&& !(str[i + 1] == DQUOTE && str[i + 2] == DQUOTE))
				element_count++;
		}
		i++;
	}
	return (element_count);
}

int	is_space_out_quotes(char c, int *quote)
{
	if (is_space(c) && !(*quote))
		return (1);
	return (0);
}

int	get_next_word_len(char *str)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i] && !is_space_out_quotes(str[i], &quote))
	{
		set_quote_mode(str[i], &quote);
		len++;
		i++;
	}
	printf("word in gnw_len = %s\n", str);
	printf("%d\n", len);
	return (len);
}

char	*ss_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		a = malloc(sizeof(char) * 1);
		if (a == NULL)
			return (NULL);
		a[0] = '\0';
		return (a);
	}
	a = (char *) malloc ((len + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
		a[i++] = s[start++];
	a[i] = '\0';
	free(s);
	s = NULL;
	return (a);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

void	get_elements(char *str, char **elements, int element_count)
{
	int	i;
	int	j;
	int	s;
	int	element_size;

	i = 0;
	j = 0;
	s = 0;
	element_size = 0;
	while (i < element_count)
	{
		element_size = get_next_word_len(str);
		j = skip_spaces(str);
		elements[i] = ft_substr(str, j, element_size + 1);
		s = skip_spaces(str) + element_size + 1;
		str = ss_substr(str, s, (ft_strlen(str) - element_size) + 1);
		i++;
	}
}

char	**smart_split(char *str)
{
	int		element_count;
	char	**elements;

	element_count = get_element_count(str);
	elements = malloc(sizeof(char *) * (element_count + 1));
	elements[element_count] = 0;
	printf("EC = %d\n-----\n", element_count);
	get_elements(str, elements, element_count);

	printf("\n\n---[Elements]---\n\n");
	for (int i = 0; i < element_count; i++) //! Remember to remove.
		printf("Element %i = %s\n", i, elements[i]);
	printf("\n\n---[Elements]---\n\n");

	return (NULL);
}
