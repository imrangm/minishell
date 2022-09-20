/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 14:54:14 by imustafa         ###   ########.fr       */
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
	if (end_pipe(line))
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
	if (pc_valid(data->line, data))
	{
		node = parse(data);
		if (!node)
			return ;
		data->root = node;
		execute_line(data);
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
