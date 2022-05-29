/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/30 01:19:09 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n');
}

static int	set_i(int *i, int *element_count, char c, int *quote)
{
	if (!is_space(c))
	{
		(*element_count)++;
		if (set_quote_mode(c, quote))
			(*i) += 2;
		else
			(*i)++;
	}
	return (*i);
}

static int	get_element_count(char *str)
{
	int		element_count;
	int		quote;
	int		i;

	element_count = 0;
	quote = 0;
	i = set_i(&i, &element_count, str[0], &quote);
	while (str[i])
	{
		if (set_quote_mode(str[i], &quote))
			i++;
		if (str[i] && is_space(str[i]) && !quote)
		{
			if (str[i + 1] && !is_space(str[i + 1]) && str[i + 1] != quote)
				element_count++;
		}
		i++;
	}
	return (element_count);
}

char	**smart_split(char *str)
{
	int	element_count;

	element_count = get_element_count(str);
	printf("%d\n", element_count);
	return (NULL);
}