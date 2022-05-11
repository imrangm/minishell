/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 19:58:07 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Checks for incorrect redirection syntax,
* forbidden chars, and unclosed quotes.
*/
int	preliminary_check(char *str, t_data *data)
{
	if ((p_is_empty_input(str)
		|| p_contains_unclosed_quotes(str)
		|| p_contains_illegal_special_chars(str)
		|| p_contains_invalid_redirs(str))
		|| p_check_end(str)
		|| p_check_pipe(str)
		|| p_check_redir(str))
	{
		data->last_exit_status = 1;
		return (0);
	}
	return (1);
}
