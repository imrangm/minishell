/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:19 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/18 18:28:55 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			ft_free_2d(check);
			ft_putstr_fd("Error: Incorrect syntax for pipes\n", 2);
			return (1);
		}
		i++;
	}
	ft_free_2d(check);
	return (0);
}
