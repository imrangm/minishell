/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/19 17:42:00 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(t_node *node, char *line, t_data *data)
{
	t_cmd	*cmd;

	check_error(node, data);
	if (!data->error)
	{
		cmd = process_command(node, count_pipes(line), data);
		if (!cmd)
		{
			printf("cmd is NULL\n");
			return ;
		}
		execute(cmd);
	}
	data->error = 0;
}

void	parse_line(char *line, t_data *data)
{
	t_node	*node;

	add_history(line);
	if (end_pipe(line))
		return ;
	data->line = trim_line(line);
	if (pc_valid(data->line, data))
	{
		node = parse(data);
		if (!node)
			return ;
		data->root = node;
		print_ast(data->root, 1);
		execute_line(data->root, line, data);
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
		ft_free(line);
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
