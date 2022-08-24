/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:00:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/24 08:19:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_pipeline(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	left = parse_command(toks);
	if (!has_more_tokens(toks) || look_ahead(toks) != PIPE)
		return (left);
	if (look_ahead(toks) == PIPE)
	{
		next_token(toks);
		right = parse_pipeline(toks);
		return (pair_node(left, right, "PIPELINE"));
	}
	next_token(toks);
	right = parse_command(toks);
	return (pair_node(left, right, "PIPELINE"));
}

t_node	*parse_command(t_token **toks)
{
	t_node	*left;
	t_node	*right;
	t_token	*token;
	int		expansion_mode;
	int		io;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	io = 0;
	expansion_mode = 0;
	if (look_ahead(toks) != WORD) //add others too
	{
		ft_free(left);
		ft_free(right);
		return (error_node(ft_strjoin("unexpected token near: ",
					current_token(toks))));
	}
	while (has_more_tokens(toks) && look_ahead(toks) != PIPE)
	{
		if (look_ahead(toks) == WORD
			|| look_ahead(toks) == SQUOTE
			|| look_ahead(toks) == DQUOTE)
		{
			next_token(toks);
			token = toks[toks[0]->iter];
			if (left->value)
			{
				token->value = ft_strjoin(left->value,
						ft_strjoin(" ", token->value));
			}
			printf("value: %s\n", token->value);
			if ((token->type == WORD || token->type == DQUOTE)
				&& ft_strchr(token->value, '$'))
			{
				expansion_mode = 1;
				printf("expansions: %d\n", expansion_mode);
			}
			left = parse_arguments(toks);
		}
		if (look_ahead(toks) == REDIR)
		{
			next_token(toks);
			if (right->right_node)
			{
				process_redirection(right->left_node->value,
					right->right_node->value);
				if ((ft_strncmp(right->left_node->value, ">>", 2) == 0
						|| ft_strncmp(right->left_node->value, ">", 1) == 0)
					&& (ft_strncmp(toks[toks[0]->iter]->value, "<<", 2) == 0
						|| ft_strncmp(toks[toks[0]->iter]->value, "<", 1) == 0))
				{
					right->id = ft_strdup("IO");
					right = parse_io(right, toks, "IO");
					io = 1;
				}
				if ((ft_strncmp(right->left_node->value, "<<", 2) == 0
						|| ft_strncmp(right->left_node->value, "<", 1) == 0)
					&& (ft_strncmp(toks[toks[0]->iter]->value, ">>", 2) == 0
						|| ft_strncmp(toks[toks[0]->iter]->value, ">", 1) == 0))
				{
					right->id = ft_strdup("IO");
					right = parse_io(right, toks, "IO");
					io = 1;
				}
			}
			if (!io)
			{
				right = parse_redirection(toks);
			}
		}
	}
	if (!left->id)
	{
		left = node(toks);
		left->id = ft_strdup("COMMAND");
		ft_free(right);
		return (left);
	}
	if (!right->id && expansion_mode)
	{
		left->id = ft_strdup("RAW");
		right = add_expansions(left);
		return (pair_node(left, right, "COMMAND"));
	}
	if (!right->id)
	{
		left->id = ft_strdup("COMMAND");
		ft_free(right);
		return (left);
	}
	if (expansion_mode)
	{
		left->type = 1;
		left->left_node = malloc(sizeof(t_node));
		left->left_node->value = ft_strdup(left->value);
		left->left_node->id = ft_strdup("RAW");
		left->left_node->type = 0;
		ft_free(left->value);
		left->right_node = add_expansions(left->left_node);
	}
	return (pair_node(left, right, "COMMAND"));
}

t_node	*parse_arguments(t_token **toks)
{
	t_node	*args;
	// t_node	*left;
	// t_node	*right;
	// t_token	*temp;
	// int		expansion_mode;

	args = node(toks);
	// expansion_mode = 0;
	// temp = current_token(toks);
	// printf("value: %s\n", temp->value);
	// if ((temp->type == WORD || temp->type == DQUOTE)
	// 	&& ft_strchr(temp->value, '$'))
	// {
	// 	expansion_mode++;
	// 	printf("expansions: %d\n", expansion_mode);
	// }
	// if (expansion_mode && !has_more_tokens(toks))
	// {
	// 	args->id = ft_strdup("RAW");
	// 	left = args;
	// 	right = add_expansions(args);
	// 	return (pair_node(left, right, "ARGS"));
	// }
	args->id = ft_strdup("ARGS");
	return (args);
}

t_node	*parse_redirection(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	left = node(toks);
	left->id = ft_strdup("OP");
	if (look_ahead(toks) != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
					current_token(toks)));
		return (pair_node(left, right, "REDIR"));
	}
	next_token(toks);
	right = node(toks);
	right->id = ft_strdup("FILE");
	return (pair_node(left, right, "REDIR"));
}

t_node	*parse_io(t_node *redir, t_token **toks, char *id)
{
	t_node	*left;
	t_node	*right;
	t_node	*pair_left;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	left = node(toks);
	left->id = ft_strdup("OP");
	if (look_ahead(toks) != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
					current_token(toks)));
		return (pair_node(left, right, "IO"));
	}
	next_token(toks);
	right = node(toks);
	right->id = ft_strdup("FILE");
	pair_left = pair_node(left, right, id);
	return (pair_node(pair_left, redir, "REDIR"));
}
