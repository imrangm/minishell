/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 21:23:04 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_more_tokens(t_token *tok)
{
	if (tok->next != NULL)
		return (1);
	else
		return (0);
}

int	look_ahead(t_token *tok)
{
	if (tok->first && !tok->cur)
		return (tok->type);
	if (tok->next != NULL)
		return (tok->next->type);
	else
		return (0);
}

// simply read tok value
char	*current_token(t_token *tok)
{
	return (tok->value);
}

void	next_token(t_token **tok)
{
	if ((*tok)->first && !(*tok)->cur)
	{
		(*tok)->cur = 1;
		return ;
	}
	else if (has_more_tokens(*tok))
		*tok = (*tok)->next;
}

void	parse(t_data *data)
{	
	t_scan	*src;
	t_token	*tok;
	t_node	*node;
	// int		count;
	char	*line;

	set_signalset(1);
	line = data->line;
	src = scan_input(line);
	tok = tokenize(src);
	print_tokens_ll(tok);
	node = parse_pipeline(tok);
	free_chars(src->chars, src->len);
	ft_free(src);
	print_ast(node, 0);
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
