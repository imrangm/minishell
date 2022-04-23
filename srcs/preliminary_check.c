/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/24 01:01:21 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks for incorrect redirection syntax,
* forbidden chars, and unclosed quotes.
*/
int	preliminary_check(char *str)
{
	if (!p_is_cmd_syntax(str) && !p_starts_with_redirection(str))
		return (0);
	if (p_contains_unclosed_quotes(str))
		return (0);
	// if (p_valid_redirection_syntax(str)) // TODO
	// 	return (0);
	// if (p_valid_flag_syntax(str)) // TODO
	// 	return (0);
	return (1);
}
