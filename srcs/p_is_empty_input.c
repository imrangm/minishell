/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is_empty_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:52:04 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/01 16:30:10 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_is_empty_input(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
