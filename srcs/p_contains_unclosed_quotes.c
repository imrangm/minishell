/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_contains_unclosed_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:48:29 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/27 14:32:14 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	p_extension(char *str, int *i, int *qf, int quote_type)
{
	(*qf) = 1;
	(*i)++;
	while (str[(*i)])
	{
		if (str[(*i)] == quote_type && str[(*i) - 1] != '\\' && (*i) != 0)
		{
			(*qf) = 0;
			break ;
		}
		(*i)++;
	}
}

int	p_contains_unclosed_quotes(char *str)
{
	int	i;
	int	sqf;
	int	dqf;

	i = 0;
	sqf = 0;
	dqf = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE)
			p_extension(str, &i, &dqf, DQUOTE);
		if (str[i] && str[i] == SQUOTE)
			p_extension(str, &i, &sqf, SQUOTE);
		else
			break ;
		i++;
	}
	if (dqf || sqf)
	{
		ft_putstr_fd("Error: Unclosed quote detected.\n", 2);
		return (1);
	}
	return (0);
}
