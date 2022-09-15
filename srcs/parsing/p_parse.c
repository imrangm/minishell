/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/15 18:57:30 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse(t_data *data)
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
	expansion(token, data);
	print_tokens(token);
	/* PARSER */
	node = parse_pipeline(toks);
	print_ast(node, 0);
	free_chars(src);
	free_tokens(token);
	ft_free(toks);
	return (node);
}
