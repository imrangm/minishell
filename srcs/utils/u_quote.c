/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:34:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/22 13:42:18 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_strippedstr_size(char *str)
{
	int	i;
	int	q;
	int	s;

	i = 0;
	q = 0;
	s = 0;
	while (str && str[i])
	{
		if (!q && ft_isquote(str[i]))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else
			s++;
        i++;
	}
	return (s + 1);
}

char	*quote_removal(char *str)
{
	int		i;
	int		j;
	int		q;
	char	*stripped_str;

	i = 0;
	j = 0;
	q = 0;
	stripped_str = malloc(sizeof(char) * get_strippedstr_size(str));
	while (str[i])
	{
		if (!q && ft_isquote(str[i]))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else
		{
			stripped_str[j] = str[i];
			j++;
		}
		i++;
	}
	stripped_str[j] = '\0';
	return (stripped_str);
}
