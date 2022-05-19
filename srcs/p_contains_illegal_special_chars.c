/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_contains_illegal_special_chars.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:32:42 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/19 14:08:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_illegal_char(char c)
{
	return (c == '\\' || c == ';' || c == '&' || c == '!' || c == '`'
		|| c == '(' || c == ')' || c == '#' || c == '*');
}

static int	print_forbidden_char_error(char c, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(" is a forbidden character.\n", 2);
	}
	else
		ft_putstr_fd("Error: Required space after ! in double quotes.\n", 2);
	return (1);
}

/*
* Detects illegal characters and prints to stderr.
*/
int	p_contains_illegal_special_chars(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = ft_strlen(str);
	quote = 0;
	while (i < j)
	{
		if (set_quote_mode(str[i], &quote))
			i++;
		if (str[i] && is_illegal_char(str[i]) && !quote)
			return (print_forbidden_char_error(str[i], 1));
		else if (i + 1 < j)
			if (str[i] && str[i] == '!' && str[i + 1] != 32
				&& quote == '\"')
				return (print_forbidden_char_error(str[i], 0));
		i++;
	}
	return (0);
}
