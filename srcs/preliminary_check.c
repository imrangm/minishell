/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/09 02:14:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks for incorrect redirection syntax,
* forbidden chars, and unclosed quotes.
*/
int	preliminary_check(char *str)
{
	return (!p_is_empty_input(str)
			&& !p_contains_unclosed_quotes(str)
			&& !p_contains_illegal_special_chars(str)
			&& !p_contains_invalid_redirs(str));
}
