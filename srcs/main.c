/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/21 18:06:12 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		{
			add_history(line);
			if (ft_strchr(line, '|'))
				pipes(line);
			if (ft_strnstr(line, "<<", ft_strlen(line)))
				here_ops(line);
			else
				execute(line);
		}
		free(line);
	}
}