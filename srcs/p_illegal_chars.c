/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_illegal_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:32:42 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/27 16:30:27 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_char_illegal(char c)
{
	return (c == '\\' || c == ';' || c == '&' || c == '#' || c == '~'
		|| c == '!' || c == '?' || c == '`' || c == '^' || c == '@'
		|| c == '%' || c == '(' || c == ')' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == ':' || c == '<' || c == '>'
		|| c == '+' || c == '_');
}

/*
* Detects illegal characters and prints to stderr.
*/
int	p_illegal_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_char_illegal(str[i]))
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
