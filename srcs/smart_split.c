/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/01 16:36:59 by nmadi            ###   ########.fr       */
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

char	**smart_split(char *str)
{
	int	element_count;

	element_count = get_element_count(str);
	printf("%d\n", element_count);
	return (NULL);
}
