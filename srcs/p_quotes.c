/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 00:48:29 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/04 21:31:28 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_quotes(char *str)
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
		i++;
	}
	if (!q)
		return (0);
	ft_putstr_fd("Error: Unclosed quote detected.\n", 2);
	return (1);
}
