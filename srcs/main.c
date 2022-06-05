/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/05 18:57:08 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(char *line, t_data *data)
{
	if (is_pipe_mode(line))
		split_pipe(line, data);
	else if (is_redir_mode(line))
		split_rd(line, data);
	else
		master_execute(line, data);
}

void	minishell(t_data *data)
{
	char	*line;

	in_minishell_var(1);
	while (isatty(STDIN_FILENO))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signals);
		line = readline("$> ");
		if (!line)
		{
			free_2d(data->envp);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			if (p_valid(line, data))
				execute_line(line, data);
		}
		else
			data->last_exit_status = 0;
		in_minishell_var(1);
		safe_free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.envp = init_envp(envp);
	data.pwd = NULL;
	data.old_pwd = NULL;
	minishell(&data);
}
