/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_AST.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:00:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 21:25:12 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_pipeline(t_token *tok)
{
	t_node	*left;
	t_node	*right;

	if (look_ahead(tok) == PIPE)
		return (error_node(ft_strjoin("unexpected token near: ",
					current_token(tok))));
	left = parse_command(tok);
	if (!has_more_tokens(tok) || look_ahead(tok) != PIPE)
		return (left);
	if (look_ahead(tok) == PIPE)
	{
		next_token(&tok);
		if (look_ahead(tok) == PIPE)
		{
			ft_free(left);
			return (error_node(ft_strjoin("unexpected token near: ",
						current_token(tok))));
		}
		right = parse_pipeline(tok);
		return (pair_node(left, right, "PIPELINE"));
	}
	next_token(&tok);
	right = parse_command(tok);
	return (pair_node(left, right, "PIPELINE"));
}

static void	parse_command_left(t_node **n, t_token *tok)
{
	if ((*n)->value)
	{
		if (tok->space)
		{
			(*n)->value = ft_strjoin_and_free((*n)->value, " ");
			(*n)->value = ft_strjoin_and_free((*n)->value, tok->value);
		}
		else
			(*n)->value = ft_strjoin_and_free((*n)->value, tok->value);
	}
	else
		(*n)->value = ft_strdup(current_token(tok));
	(*n)->id = "ARGS";
}

static void	parse_command_right(t_node **n, t_token *tok)
{
	int		io;
	int		pr;

	io = 0;
	pr = 0;
	if ((*n)->right_node)
	{
		pr = process_redirection(&(*n)->left_node,
				&(*n)->right_node, current_token(tok));
		if (pr == -1)
			return ;
		if (check_io((*n)->left_node->value, current_token(tok)))
		{
			(*n)->id = "IO";
			(*n) = parse_io((*n), tok, "IO");
			io = 1;
		}
	}
	if (!io)
	{
		if (pr)
			free_pair((*n)->left_node, (*n)->right_node);
		ft_free(*n);
		(*n) = parse_redirection(tok);
	}
}

static t_node	*command_return(t_node **lf, t_node **rt, t_token *tok)
{
	if (!(*lf)->id)
	{
		ft_free(*rt);
		(*lf)->value = ft_strdup(current_token(tok));
		(*lf)->id = "COMMAND";
		return (*lf);
	}
	if (!(*rt)->id)
	{
		(*lf)->id = "COMMAND";
		ft_free(*rt);
		return (*lf);
	}
	return (pair_node(*lf, *rt, "COMMAND"));
}

t_node	*parse_command(t_token *tok)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	while (has_more_tokens(tok) && look_ahead(tok) != PIPE)
	{
		if (look_ahead(tok) != REDIR)
		{
			next_token(&tok);
			parse_command_left(&left, tok);
			// printf("tok t: %d, f: %d, c: %d, v: %s\n",
			// 	tok->type, tok->first, tok->cur, tok->value);
		}
		if (look_ahead(tok) == REDIR)
		{
			next_token(&tok);
			parse_command_right(&right, tok);
		}
	}
	// exit(0);
	return (command_return(&left, &right, tok));
}
