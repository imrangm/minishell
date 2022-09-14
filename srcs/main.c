/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/14 16:52:38 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(t_node *node, char *line, t_data *data)
{
	data->error = 0;
	check_error(node, data);
	if (!data->error)
		execute(process_command(node, count_pipes(line), data),
			data);
	data->error = 0;
}

void	parse_line(char *line, t_data *data)
{
	t_node	*node;

	end_pipe(&line);
	add_history(line);
	data->line = trim_line(line);
	if (pc_valid(data->line, data))
	{
		node = parse(data);
		data->root = node;
		execute_line(node, line, data);
		free_nodes(data->root);
	}
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
		if (check_space(line))
			continue ;
		if (line[0])
			parse_line(line, data);
		ft_free(data->line);
		ft_free(line);
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
