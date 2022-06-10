/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/10 15:24:33 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

int	pc_pipe(char *line)
{
	int		i;
	char	**check;

	i = 0;
	check = ft_split(line, ' ');
	while (check[i + 1])
	{
		if ((ft_strncmp(check[i], "|", 1)) == 0
			&& (ft_strncmp(check[i + 1], "|", 1) == 0))
		{
			free_2d(check);
			return (error("minishell: syntax error\n"));
		}
		i++;
	}
	free_2d(check);
	return (0);
}