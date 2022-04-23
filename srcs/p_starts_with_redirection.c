/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_starts_with_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:52:48 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/24 00:53:02 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks if the line starts with > or >>
*/
int	p_starts_with_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i + 1])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (1);
		else if (str[i] == '>' && str[i + 1] != '>')
			return (1);
	}
	return (0);
}
