/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/22 15:41:16 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	preliminary_check(char *str, t_data *data)
{
	if (p_is_empty_input(str))
	{
		data->last_exit_status = 0;
		return (0);
	}
	if (p_contains_unclosed_quotes(str)
		|| p_contains_illegal_special_chars(str)
		|| p_contains_invalid_redirs(str)
		|| p_check_end(str)
		|| p_check_pipe(str)
		|| p_check_redir(str)
		|| p_env_error(str))
	{
		data->last_exit_status = 1;
		return (0);
	}
	data->last_exit_status = 0;
	return (1);
}
