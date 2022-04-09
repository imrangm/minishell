/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/09 18:18:15 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
int	main(int ac, char **av)
{
	char	*line;

	(void) ac;
	(void) av;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		execute(line);
		free(line);
	}
}