/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/20 17:35:12 by imustafa         ###   ########.fr       */
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
	t_scan	*src;
	t_token	**toks;
	t_node	*node;
	int		count;

	while (isatty(STDIN_FILENO))
	{
		set_signalset(0);
		line = readline("$> ");
		if (!line)
		{
			ft_free_2d(data->envp);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			/* new parser */
			src = scan_input(line);
			test_scan(line);
			toks = tokenize(src);
			test_tokenize(src);
			node = parse(toks);
			count = visit(node, 0);
			traverse(node, count, data);
			free_chars(src->chars, src->len);
			free_tokens(toks);
			free_nodes(node);
			/* old parser */
			// if (pc_valid(line, data))
			// 	execute_line(line, data);
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
