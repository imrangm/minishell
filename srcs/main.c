/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/21 13:11:15 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(char *line, t_data *data)
{
	int	len;

	set_signalset(1);
	len = ft_strlen(line) - 1;
	if (line[len] == '|')
		line = ft_strjoin(line, line_update());
	if (pc_mode(line, 'p'))
		handle_pp(line, data);
	else if (pc_mode(line, 'r'))
		execute_rd(line, data);
	else
		master_execute(line, data);
}

void	minishell(t_data *data)
{
	char	*line;

	while (isatty(STDIN_FILENO))
	{
		set_signalset(0);
		line = readline("$> ");
		if (!line)
		{
			free_data(data);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			if (pc_valid(line, data))
				execute_line(line, data);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.last_exit_status = 0;
	init_envp(envp, &data);
	minishell(&data);
}

//! Problem with delete_env() – b_unset is based on it