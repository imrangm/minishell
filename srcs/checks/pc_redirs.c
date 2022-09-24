/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:09:27 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:09:27 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_single(char *str, int i)
{
	if ((str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '<' && (str[i + 1] == '>' || str[i + 1] == '|'))
		|| (str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '|' && str [i + 1] == '|'))
	{
		ft_putstr_fd("Error: Invalid syntax.\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_double(char *str, int i)
{
	if (((str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == '|'
					|| str[i + 2] == '<' || str[i + 2] == '>')))
		|| (str[i] == '<' && str[i + 1] == '<'
			&& (str[i + 2] == '|' || str[i + 2] == '<'
				|| str[i + 2] == '>')))
	{
		ft_putstr_fd("Error: Invalid syntax.\n", 2);
		return (1);
	}
	return (0);
}

int	pc_redirs(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (i < j)
	{
		if (i + 1 < j)
		{
			if (handle_single(str, i))
				return (1);
		}
		if (i + 2 < j)
		{
			if (handle_double(str, i))
				return (1);
		}
		i++;
	}
	return (0);
}
