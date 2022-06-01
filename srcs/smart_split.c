/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/01 16:30:13 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == DQUOTE || c == SQUOTE);
}

// static int	last_element_check(char *str, int i)
// {
// 	while (str[i])
// 	{
// 		if (!is_space(str[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	consecutive_quote_check(char c, char d)
// {
// 	return ((c == SQUOTE && d == SQUOTE) || (c == DQUOTE && d == DQUOTE));
// }

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
			element_count++;
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
