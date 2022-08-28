/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/28 12:01:10 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			free_data(data);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			/* new parser */
			src = scan_input(line);
			// test_scan(line);
			toks = tokenize(src);
			// test_tokenize(src);
			node = parse(toks);
			print_ast(node, 0);
			count = visit(node, 0);
			execute(node, count, data);
			free_chars(src->chars, src->len);
			ft_free(src);
			free_tokens(toks);
			free_nodes(node);
			// 	printf("----------------------------\n");
			// free_node(node);
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
