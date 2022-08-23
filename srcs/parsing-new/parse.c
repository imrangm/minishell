/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/23 10:35:17 by imustafa         ###   ########.fr       */
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

t_token	*current_token(t_token **toks)
{
	return(toks[toks[0]->iter]);
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

t_node	*parse(t_token **toks)
{
	if (look_ahead(toks) == PIPE)
	{
		return (error_node(ft_strjoin("unexpected token near: ",
					toks[toks[0]->iter]->value)));
	}
	return (parse_pipeline(toks));
}

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
		if (look_ahead(toks) != WORD)
		{
			right = error_node(ft_strjoin("unexpected token near: ",
						toks[toks[0]->iter]->value));
			return (right);
		}
		right = parse_pipeline(toks);
		return (pair_node(left, right, "PIPELINE"));
	}
	next_token(toks);
	if (look_ahead(toks) != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
					toks[toks[0]->iter]->value));
		return (right);
	}
	right = parse_command(toks);
	return (pair_node(left, right, "PIPELINE"));
}

t_node	*parse_command(t_token **toks)
{
	t_node	*left;
	t_node	*right;
	t_token	*temp;
	int		expansion_mode;
	int		io;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	io = 0;
	expansion_mode = 0;
	if (toks[0]->count == 1
		&& (toks[0]->type != PIPE || toks[0]->type != REDIR))
	{
		left = node(toks);
		left->id = ft_strdup("COMMAND");
		return (left);
	}
	while (has_more_tokens(toks) && look_ahead(toks) != PIPE)
	{
		if (look_ahead(toks) == WORD
			|| look_ahead(toks) == SQUOTE
			|| look_ahead(toks) == DQUOTE)
		{
			next_token(toks);
			if (left->value) //* may seg fault
			{
				toks[toks[0]->iter]->value = ft_strjoin(left->value,
						ft_strjoin(" ", toks[toks[0]->iter]->value));
			}
			temp = current_token(toks);
			printf("value: %s\n", temp->value);
			if ((temp->type == WORD || temp->type == DQUOTE)
				&& ft_strchr(temp->value, '$'))
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
				// printf("value: %s, %s\n", toks[toks[0]->iter]->value, right->left_node->value);
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
		printf("X0\n");
		left = node(toks);
		left->id = ft_strdup("COMMAND");
		ft_free(right);
		return (left);
	}
	if (!right->id && expansion_mode)
	{
		printf("X1\n");
		left->id = ft_strdup("RAW");
		right = add_expansions(left);
		return (pair_node(left, right, "COMMAND"));
	}
	if (!right->id)
	{
		printf("X1\n");
		left->id = ft_strdup("COMMAND");
		ft_free(right);
		return (left);
	}
	if (expansion_mode)
	{
		printf("HEREX\n");
		left->type = 1;
		left->left_node = malloc(sizeof(t_node));
		left->left_node->value = ft_strdup(left->value);
		left->left_node->id = ft_strdup("RAW");
		left->left_node->type = 0;
		ft_free(left->value);
		left->right_node = add_expansions(left->left_node);
	}
	printf("X2\n");
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
			toks[toks[0]->iter]->value));
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
			toks[toks[0]->iter]->value));
		return (pair_node(left, right, "IO"));
	}
	next_token(toks);
	right = node(toks);
	right->id = ft_strdup("FILE");
	pair_left = pair_node(left, right, id);
	return (pair_node(pair_left, redir, "REDIR"));
}

void	test_parse(t_token **toks)
{
	t_node	*ret;

	ret = parse(toks);
		printf("------------------------\n");
	printf("AST\n");
	visit(ret, 0);
}