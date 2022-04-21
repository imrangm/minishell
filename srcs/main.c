/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/22 00:43:52 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
int	main(void)
{
	char		*line;
	extern int	rl_catch_signals;

	rl_catch_signals = 0;

	while (isatty(STDIN_FILENO))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signals);
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
