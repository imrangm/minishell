/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:05:40 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/09 18:18:55 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nart.h"

/*
* Displays a prompt and adds
* each entered input to history.
*/
void	minishell(void)
{
	char	*line;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		if (is_valid(line))
			; //* Exec.
		free(line);
	}
}
