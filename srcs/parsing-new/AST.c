/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:00:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/27 14:06:31 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_pipeline(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = parse_command(toks);
	if (!has_more_tokens(toks) || look_ahead(toks) != PIPE)
	{
		return (left);
	}
	if (look_ahead(toks) == PIPE)
	{
		next_token(toks);
		if (look_ahead(toks) == PIPE)
		{
			ft_free(left);
			return (error_node(ft_strjoin("unexpected token near: ",
						current_token(toks))));
		}
		right = parse_pipeline(toks);
		return (pair_node(left, right, "PIPELINE"));
	}
	next_token(toks);
	right = parse_command(toks);
	return (pair_node(left, right, "PIPELINE"));
}

void	parse_command_left(t_node **n, int *exp, t_token **toks)
{
	t_token	*token;

	token = toks[toks[0]->iter];
	if ((*n)->value)
	{
		(*n)->value = ft_strjoin_and_free((*n)->value, " ");
		(*n)->value = ft_strjoin_and_free((*n)->value, token->value);
	}
	else
		(*n)->value = ft_strdup(current_token(toks));
	if ((token->type == WORD || token->type == DQUOTE)
		&& ft_strchr(token->value, '$'))
	{
		*exp = 1;
	}
	(*n)->id = "ARGS";
}

void	parse_command_right(t_node **n, t_token **toks)
{
	int		io;
	int		pr;

	io = 0;
	pr = 0;
	if ((*n)->right_node)
	{
		pr = process_redirection(&(*n)->left_node,
				&(*n)->right_node);
		if (check_io((*n)->left_node->value, current_token(toks)))
		{
			(*n)->id = "IO";
			(*n) = parse_io((*n), toks, "IO");
			io = 1;
		}
	}
	if (!io)
	{
		if (pr)
			free_pair((*n)->left_node, (*n)->right_node);
		ft_free(*n);
		(*n) = parse_redirection(toks);
	}
}

t_node	*command_return(t_node **lf, t_node **rt, int *exp, t_token **toks)
{
	if (!(*lf)->id)
	{
		ft_free(*rt);
		(*lf)->value = ft_strdup(current_token(toks));
		(*lf)->id = "COMMAND";
		return (*lf);
	}
	if (!(*rt)->id && *exp)
	{
		(*lf)->id = "RAW";
		ft_free(*rt);
		(*rt) = add_expansions(*lf);
		return (pair_node(*lf, *rt, "COMMAND"));
	}
	if (!(*rt)->id)
	{
		(*lf)->id = "COMMAND";
		ft_free(*rt);
		return (*lf);
	}
	if (*exp)
		expansion_node(lf);
	return (pair_node(*lf, *rt, "COMMAND"));
}

t_node	*parse_command(t_token **toks)
{
	t_node	*left;
	t_node	*right;
	int		expansion_mode;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	expansion_mode = 0;
	while (has_more_tokens(toks) && look_ahead(toks) != PIPE)
	{
		if (look_ahead(toks) != REDIR)
		{
			next_token(toks);
			parse_command_left(&left, &expansion_mode, toks);
		}
		if (look_ahead(toks) == REDIR)
		{
			next_token(toks);
			parse_command_right(&right, toks);
		}
	}
	return (command_return(&left, &right, &expansion_mode, toks));
}
