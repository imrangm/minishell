/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/15 19:46:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_toklist	*tokenizer(t_data *data)
{
	t_charlist	*src;
	t_toklist	*toks;
	t_token		*token;
	char		*line;

	line = data->line;
	src = scan_input(line);
	toks = tokenize(src);
	token = toks->first;
	expansion(token, data);
	print_tokens(token);
	free_chars(src);
	return (toks);
}

t_node	*parse(t_data *data)
{
	t_toklist	*toks;
	t_node		*node;

	set_signalset(1);
	toks = tokenizer(data);
	node = parse_pipeline(toks);
	print_ast(node, 0);
	free_tokens(toks->first);
	ft_free(toks);
	return (node);
}
