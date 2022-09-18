/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/16 13:38:46 by imustafa         ###   ########.fr       */
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
	free_tokens(toks->first);
	ft_free(toks);
	return (node);
}