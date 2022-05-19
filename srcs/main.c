/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/19 05:25:07 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	(void) argc;
	(void) argv;
	data.envp = clone_env(envp, 0);
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
			// line = ft_strtrim(line, "\n ");
			if (preliminary_check(line, &data))
			{
				if (ft_strchr(line, '|'))
					split_pipe(line, &data);
				else if (ft_strchr(line, '<') || ft_strchr(line, '>'))
					split_rd(line, &data);
				else
					master_execute(line, &data);
			}
		}
		else
			data.last_exit_status = 0;
		in_minishell_var(1);
		free(line);
	}
}
