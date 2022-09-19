/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_AST.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:00:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/19 17:44:15 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_pipeline(t_toklist *toks)
{
	t_node	*left;
	t_node	*right;

	if (look_ahead(toks) == PIPE)
		return (error_node(ft_strjoin("unexpected token near: ",
					current_token(toks))));
	left = parse_command(toks);
	if (!has_more_tokens(toks) || look_ahead(toks) != PIPE)
		return (left);
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

static void	parse_command_left(t_node **n, t_toklist *toks)
{
	if ((*n)->value)
	{
		if (toks->current->space)
		{
			(*n)->value = ft_strjoin_and_free((*n)->value, " ");
			(*n)->value = ft_strjoin_and_free((*n)->value, current_token(toks));
		}
		else
			(*n)->value = ft_strjoin_and_free((*n)->value, current_token(toks));
	}
	else
		(*n)->value = ft_strdup(current_token(toks));
	(*n)->id = "ARGS";
}

static void	parse_command_right(t_node **n, t_toklist *toks)
{
	int		io;
	int		pr;

	io = 0;
	pr = 0;
	if ((*n)->right)
	{
		pr = process_redirection(&(*n)->left, &(*n)->right,
				current_token(toks));
		if (pr == -1)
			return ;
		if (check_io((*n)->left->value, current_token(toks)))
		{
			(*n)->id = "IO";
			(*n) = parse_io((*n), toks, "IO");
			io = 1;
		}
	}
	if (!io)
	{
		if (pr)
			free_pair((*n)->left, (*n)->right);
		ft_free(*n);
		(*n) = parse_redirection(toks);
	}
}

static t_node	*command_return(t_node **lf, t_node **rt, t_toklist *toks)
{
	// if ((*rt)->value[0] == '<')
	// 	printf("X\n");
	if (!(*lf)->id)
	{
		ft_free(*rt);
		(*lf)->value = ft_strdup(current_token(toks));
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

t_node	*parse_command(t_toklist *toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	while (has_more_tokens(toks) && look_ahead(toks) != PIPE)
	{
		// printf("tok value: %s\n", current_token(toks));
		if (look_ahead(toks) != REDIR)
		{
			next_token(toks);
			parse_command_left(&left, toks);
		}
		if (look_ahead(toks) == REDIR)
		{
			next_token(toks);
			parse_command_right(&right, toks);
		}
	}
	return (command_return(&left, &right, toks));
}
