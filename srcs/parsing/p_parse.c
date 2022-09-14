/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/14 09:03:19 by imustafa         ###   ########.fr       */
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

// simply read tok value
char	*current_token(t_toklist *toks)
{
	return (toks->current->value);
}

void	next_token(t_toklist *toks)
{
	if (!toks->current)
	{
		toks->current = toks->first;
	}
	else if (has_more_tokens(toks))
	{
		toks->current = toks->current->next;
	}
}

void	parse(t_data *data)
{	
	t_scan		*src;
	t_toklist	*toks;
	t_token		*token;
	t_node		*node;
	// int		count;
	char		*line;

	set_signalset(1);
	line = data->line;
	src = scan_input(line);
	toks = tokenize(src);
	token = toks->first;
	print_tokens_ll(token);
	node = parse_pipeline(toks);
	free_chars(src->chars, src->len);
	ft_free(src);
	print_ast(node, 0);
	free_tokens(token);
	ft_free(toks);
	// data->root = node;
	// count = count_pipes(line);
	// data->error = 0;
	// check_error(node, data);
	// if (!data->error)
	// 	process_tree(node, count, data);
	// data->error = 0;
	// free_nodes(data->root);
}
