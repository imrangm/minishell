/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/08 17:41:31 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

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