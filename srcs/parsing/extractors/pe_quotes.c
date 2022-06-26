/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:04:57 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/25 19:15:08 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_without_quotes(char *str)
{
	int		i;
	int		q;
	int		c;

	i = 0;
	q = 0;
	c = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else
			c++;
		i++;
	}
	printf("Count without quotes = %d", c);
	return (c);
}

static char	*copy_without_quotes(char *str, int	count)
{
	int		i;
	int		j;
	int		q;
	char	*ql_str;

	i = 0;
	j = 0;
	q = 0;
	ql_str = malloc(sizeof(char) * count + 1);
	ql_str[count] = '\0';
	while (str[i] && j < count + 1)
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (str[i] == q)
			q = 0;
		else // && j < count
		{
			ql_str[j] = str[i];
			// printf("%c", ql_str[j]);
			j++;
		}
		i++;
	}
	return (ql_str);
}

char	**strip_quotes(char **elements, int element_count)
{
	int		i;
	int		j;
	int		q;
	char	**stripped_elements;

	i = 0;
	j = 0;
	q = 0;
	stripped_elements = malloc(sizeof(char *) * element_count + 1);
	stripped_elements[element_count] = 0;
	while (i < element_count)
	{
		stripped_elements[i] = copy_without_quotes(elements[i],
			count_without_quotes(elements[i]));
		printf("|%s|\n", stripped_elements[i]);
		i++;
	}
	free_2d(elements);
	return (stripped_elements);
}
