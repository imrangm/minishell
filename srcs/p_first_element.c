/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_first_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:52:04 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/24 14:49:03 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks if the user has input a word at the start
* regardless whether or not it's an existing command.
*/
int	p_first_element(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (!str[i])
		return (0);
	return (1);
}
