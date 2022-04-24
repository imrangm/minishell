/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_contains_invalid_redirs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:40:44 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/24 16:57:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_single(char *str, int i)
{
	return ((str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '<' && (str[i + 1] == '>' || str[i + 1] == '|'))
		|| (str[i] == '|' && (str[i + 1] == '>' || str[i + 1] == '<')));
}

static int	handle_double(char *str, int i)
{
	return (((str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == '|'
					|| str[i + 2] == '<' || str[i + 2] == '>')))
		|| (str[i] == '>' && str[i + 1] == '>'
			&& (str[i + 2] == '|' || str[i + 2] == '<'
				|| str[i + 2] == '>')));
}

int	p_contains_invalid_redirs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if (handle_single(str, i))
			{
				ft_putstr_fd("Error: Invalid redirection syntax.\n", 2);
				return (1);
			}
		}
		if (str[i + 2])
		{
			if (handle_double(str, i))
			{
				ft_putstr_fd("Error: Invalid redirection syntax.\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
