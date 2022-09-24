/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 15:01:33 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(t_data *data)
{
	t_cmd	*cmd;
	t_node	*root;
	char	*line;
	int		p;

	root = data->root;
	line = data->line;
	check_error(root, data);
	if (!data->error)
	{
		p = count_pipes(line);
		cmd = process_command(root, p, data);
		execute(cmd);
	}
	data->error = 0;
}

void	update_line(char *line, t_data *data)
{
	if (!pc_start(line, data) && end_pipe(line))
	{
		data->line = read_pipe(line);
		add_history(data->line);
	}
	else
	{
		add_history(line);
		data->line = trim_line(line);
	}
}

void	parse_line(char *line, t_data *data)
{
	t_node	*node;

	update_line(line, data);
	if (data->line[0] != '|' && pc_valid(data->line, data))
	{
		node = parse(data);
		if (!node)
			return ;
		data->root = node;
		// print_ast(node, 2);
		execute_line(data);
		free_nodes(data->root);
	}
}

void	minishell(t_data *data)
{
	char	*line;

	g_glb.last_exit_status = &data->last_exit_status;
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
		{
			add_history(line);
			continue ;
		}
		if (line[0])
			parse_line(line, data);
		ft_free(data->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.last_exit_status = 0;
	data.error = 0;
	init_envp(envp, &data);
	minishell(&data);
}
