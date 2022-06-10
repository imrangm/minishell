/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:14:37 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/10 15:24:26 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

int	pc_end(char *line) //? Imran
{
	int	len;

	len = ft_strlen(line);
	if (line[0] == '|' || line[len - 1] == '|') //! Ignore all types of ft_isspace() after it.
		return (error("Error: Last character must not be a pipe symbol.\n"));
	else if (line[len - 1] == '>' || line[len - 1] == '<') //! Ignore all types of ft_isspace() after it.
		return (error("Error: Last character must not be a redirection symbol.\n"));
	return (0);
}
