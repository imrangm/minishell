/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_mode_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:07:08 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/05 19:26:00 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_mode(char *str, char mode)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (mode == 'p' && str[i] == '|' && !q)
			return (1);
		else if (mode == 'r' && (str[i] == '>' || str[i] == '<') && !q)
			return (1);
		i++;
	}
	return (0);
}
