/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/22 18:03:11 by nmadi            ###   ########.fr       */
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
	print_tokens(token);
	free_chars(src);
	if (expansion(toks, token, data))
		return (NULL);
	return (toks);
}

t_node	*parse(t_data *data)
{
	t_toklist	*toks;
	t_node		*node;

	set_signalset(1);
	toks = tokenizer(data);
	if (!toks)
		return (NULL);
	node = parse_pipeline(toks);
	// print_ast(node, 1);
	free_tokens(toks->first);
	ft_free(toks);
	return (node);
}
