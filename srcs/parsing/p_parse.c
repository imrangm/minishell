/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/14 13:15:13 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_more_tokens(t_toklist *toks)
{
	if (!toks->current)
		return (1);
	else if (toks->current->next != NULL)
		return (1);
	else
		return (0);
}

int	look_ahead(t_toklist *toks)
{
	if (!toks->current)
		return (toks->first->type);
	else if (toks->current->next != NULL)
		return (toks->current->next->type);
	else
		return (0);
}

char	*current_token(t_toklist *toks)
{
	return (toks->current->value);
}

void	next_token(t_toklist *toks)
{
	if (!toks->current)
		toks->current = toks->first;
	else if (has_more_tokens(toks))
		toks->current = toks->current->next;
}

void	parse(t_data *data)
{	
	t_charlist	*src;
	t_toklist	*toks;
	t_token		*token;
	t_node		*node;
	char		*line;

	set_signalset(1);
	line = data->line;
	/* TOKENIZER */
	src = scan_input(line);
	toks = tokenize(src);
	token = toks->first;
	print_tokens(token);
	/* PARSER */
	node = parse_pipeline(toks);
	print_ast(node, 0);
	free_chars(src);
	free_tokens(token);
	ft_free(toks);
	/* PROCESS && EXECUTE */
	data->root = node;
	data->error = 0;
	check_error(node, data);
	if (!data->error)
		execute(process_command(node, count_pipes(line), data), data);
	data->error = 0;
	free_nodes(data->root);
}
