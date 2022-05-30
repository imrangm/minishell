/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:14:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/30 15:16:54 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n');
}

static int	get_element_count(char *str)
{
	int		i;
	int		quote;
	int		element_count;

	i = 0;
	quote = 0;
	element_count = 0;
	while (str[i])
	{
		if (!quote && (str[i] == SQUOTE || str[i] == DQUOTE))
			quote = str[i];
		else if (quote && str[i] == quote)
		{
			while (str[i] && !is_space(str[i]))
			{

			}
		}
		else if (!quote && is_space(str[i]))
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