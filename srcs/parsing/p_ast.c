/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:19:47 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:10:26 by nmadi            ###   ########.fr       */
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
			ft_free(left->value);
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
	if ((*n)->right && ft_strcmp((*n)->id, "REDIR") == 0)
	{
		pr = process_redirection(&(*n)->left, &(*n)->right,
				current_token(toks));
		if (pr == -1)
			return ;
		u_check_io(n, toks, &io);
	}
	if (!io)
	{
		if (pr)
			free_pair((*n)->left, (*n)->right);
		ft_free(*n);
		(*n) = parse_redirection(toks, "REDIR");
	}
	else
		process_io(n, toks);
}

static t_node	*command_return(t_node **lf, t_node **rt, t_toklist *toks)
{
	if ((*rt)->id && !(*lf)->id)
	{
		ft_free(*lf);
		return (*rt);
	}
	if (!(*lf)->id && !(*rt)->id)
	{
		ft_free(*rt);
		(*lf)->value = ft_strdup(current_token(toks));
		(*lf)->id = "COMMAND";
		return (*lf);
	}
	else if (!(*rt)->id)
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
