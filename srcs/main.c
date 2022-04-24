/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/24 17:31:49 by imustafa         ###   ########.fr       */
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
			else if (ft_strnstr(line, "<<", ft_strlen(line)))
				here_ops(line);
			else if (ft_strnstr(line, ">>", ft_strlen(line)))
				append(line);
			else if (ft_strchr(line, '<') || ft_strchr(line, '>'))
				file(line);
			else
				execute(line);
		}
		free(line);
	}
}