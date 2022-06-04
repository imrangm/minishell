/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_chars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:32:42 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/04 21:34:03 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_chars(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && !q)
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (!q && (str[i] == '\\' || str[i] == ';' || str[i] == '&'
				|| str[i] == '!' || str[i] == '`' || str[i] == '(' || str[i] == ')'
				|| str[i] == '#' || str[i] == '*'))
		{
			ft_putstr_fd("Error: ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putstr_fd(" is a forbidden character.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
