/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/03 12:50:17 by imustafa         ###   ########.fr       */
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

void	parse(char *line, t_data *data)
{	
	t_scan	*src;
	t_token	**toks;
	t_node	*node;
	int		count;

	set_signalset(1);
	src = scan_input(line);
	toks = tokenize(src);
	node = parse_pipeline(toks);
	free_chars(src->chars, src->len);
	ft_free(src);
	free_tokens(toks);
	data->root = node;
	print_ast(node, 0);
	count = count_pipes(line);
	if (pc_valid(line, data))
	{
		data->error = 0;
		check_error(node, data);
		if (!data->error)
			process_tree(node, count, data);
	}
	data->error = 0;
	free_nodes(data->root);
}
