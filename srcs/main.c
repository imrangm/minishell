/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/25 22:29:50 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
int	main(void)
{
	char	*line;

	in_minishell_var(1);
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
			if (preliminary_check(line))
			{
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
		}
		in_minishell_var(1);
		free(line);
	}
}
