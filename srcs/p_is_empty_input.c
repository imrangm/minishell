/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is_empty_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:52:04 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/08 23:02:19 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks if the user has input a word at the start
* regardless whether or not it's an existing command.
*/
int	p_is_empty_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (!str[i])
		return (1);
	return (0);
}
