/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/21 21:14:48 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Ctrl + C = SIGINT - Should display a new prompt on a new line
* Ctrl + D = EOF (Not a signal) - Should exit the shell
* Ctrl + \ = SIGQUIT - Should do nothing
*/

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
int	main(void)
{
	char	*line;

	while (isatty(STDIN_FILENO))
	{
		line = readline("$> ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			if (is_valid_input(line))
			{
				if (ft_strchr(line, '|'))
					pipes(line);
				else
					execute(line);
			}
		}
		free(line);
	}
}
