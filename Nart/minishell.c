/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:05:40 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/07 13:24:07 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nart.h"

void	minishell(void)
{
	char	*line;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		if (ft_strlen(line))
			add_history(line);
		free(line);
	}
}
