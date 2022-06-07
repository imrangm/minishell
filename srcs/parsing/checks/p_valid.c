/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_valid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/07 15:53:54 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	p_valid(char *line, t_data *data)
{
	if (ft_arespaces(line))
	{
		data->last_exit_status = 0;
		return (0);
	}
	if (p_quotes(line) || p_chars(line) || p_export(line) || p_redirs(line)
		|| p_check_end(line) || p_check_pipe(line) || p_check_redir(line))
	{
		data->last_exit_status = 1;
		return (0);
	}
	data->last_exit_status = 0;
	return (1);
}
