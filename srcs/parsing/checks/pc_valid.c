/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/02 15:32:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pc_valid(char *line, t_data *data)
{
	if (ft_arespaces(line))
		return (0);
	if (pc_quotes(line) || pc_chars(line) || pc_redirs(line)
		|| pc_end(line) || pc_pipe(line) || pc_redir(line))
	{
		data->last_exit_status = 1;
		return (0);
	}
	return (1);
}
