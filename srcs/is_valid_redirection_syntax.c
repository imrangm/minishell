/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_redirection_syntax.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 03:09:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/21 19:27:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	determiner(char *str, int *i, int quote_mode, char direction)
{
	if (quote_mode)
		return (0);
	if (str[(*i) + 1])
	{
		if (str[(*i) + 1] == direction)
		{
			if (str[(*i) + 2])
			{
				if ((str[(*i) + 2]) != '>' && (str[(*i) + 2]) != '<')
				{
					(*i) += 2;
					return (1);
				}
			}
		}
		else if (str[(*i) + 1] != '>' && str[(*i) + 1] != '<')
		{
			(*i)++;
			return (1);
		}
	}
	return (0);
}

//! Fix this crap
int	is_valid_redirection_syntax(char *str, char quote)
{
	int		i;
	int		quote_mode;
	char	direction;

	i = 0;
	quote_mode = 0;
	while (str[i])
	{
		if (str[i] == quote && !quote_mode)
			quote_mode = 1;
		else if (str[i] == quote && quote_mode)
			quote_mode = 0;
		else if (str[i] == '>' || str[i] == '<')
		{
			direction = str[i];
			if (!determiner(str, &i, quote_mode, direction))
				return (0);
		}
			i++;
	}
	return (1);
}
