/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/01 19:49:29 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == DQUOTE || c == SQUOTE);
}

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

void	get_elements(char *str, char **elements)
{
	int	i;
	int	j;
	int	q;
	int	start;
	int	end;

	i = 0;
	j = 0;
	q = 0;
	start = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == q)
		{
			q = 0;
			if (str[i + 1] && !is_quote(str[i + 1]))
			{
				end = i + 1;
				elements[j] = ft_substr(str, start, end - start);
				j++;
			}
		}
		else if (is_quote(str[i]) && !q)
		{
			q = str[i];
			start = i;
		}
		// else if (!is_space(str[i]) && !is_quote(str[i]) && !q)
		// {
		// 	start = i;
		// 	if (q)
		// 		while (str[i] && str[i] != q)
		// 			i++;
		// 	end = i;
		// 	j++;
		// }
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
	printf("%d\n\n", element_count);
	get_elements(str, elements);
	for (int i = 0; i < element_count; i++)
		printf("%s\n", elements[i]);

	return (NULL);
}
