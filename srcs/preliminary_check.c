/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/25 21:04:05 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks for incorrect redirection syntax,
* forbidden chars, and unclosed quotes.
*/
int	preliminary_check(char *str)
{
	if (!p_first_element(str))
		return (0);
	if (p_contains_unclosed_quotes(str))
		return (0);
	if (p_contains_backslashes(str) || p_contains_semicolons(str))
		return (0);
	if (p_contains_invalid_redirs(str))
		return (0);
	return (1);
}
