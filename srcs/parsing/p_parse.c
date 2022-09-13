/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 19:09:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_more_tokens(t_token **toks)
{
	return ((toks[0]->iter + 1) < toks[0]->count);
}

int	look_ahead(t_token **toks)
{
	t_token	ret;
	int		i;

	ret.value = 0;
	ret.type = 0;
	if (!has_more_tokens(toks))
		return (ret.type);
	if (!toks[0]->cur)
		return (toks[0]->type);
	i = toks[0]->iter;
	ret = *toks[i + 1];
	return (ret.type);
}

char	*current_token(t_token **toks)
{
	return (toks[toks[0]->iter]->value);
}

void	next_token(t_token **toks)
{
	if (toks[0]->cur && has_more_tokens(toks))
	{
		toks[0]->iter++;
	}
	if (!toks[0]->iter && has_more_tokens(toks))
	{
		toks[0]->iter = 0;
		toks[0]->cur = 1;
	}
}

void	parse(t_data *data)
{	
	t_scan	*src;
	t_token	*tok;
	// t_node	*node;
	// int		count;
	char	*line;

	set_signalset(1);
	line = data->line;
	src = scan_input(line);
	tok = tokenize(src);
	print_tokens_ll(tok);
	// node = parse_pipeline(tok);
	free_chars(src->chars, src->len);
	ft_free(src);
	// free_tokens(tok);
	// data->root = node;
	// count = count_pipes(line);
	// data->error = 0;
	// check_error(node, data);
	// if (!data->error)
	// 	process_tree(node, count, data);
	// data->error = 0;
	// free_nodes(data->root);
}
