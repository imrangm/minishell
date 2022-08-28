/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:06:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/27 13:39:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_node	*node(t_token **toks)
// {
// 	t_node	*word;
// 	int		i;

// 	i = toks[0]->iter;
// 	word = malloc(sizeof(t_node));
// 	ft_memset(word, 0, sizeof(t_node));
// 	word->value = ft_strdup(toks[i]->value);
// 	word->left_node = NULL;
// 	word->right_node = NULL;
// 	return (word);
// }

t_node	*pair_node(t_node *left, t_node *right, char *id)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	ft_memset(new, 0, sizeof(t_node));
	new->id = id;
	new->type = 1;
	new->left_node = left;
	new->right_node = right;
	return (new);
}

t_node	*error_node(char *msg)
{
	t_node	*err;

	err = malloc(sizeof(t_node));
	ft_memset(err, 0, sizeof(t_node));
	err->value = (msg);
	err->type = 2;
	err->id = "ERROR";
	return (err);
}

void	expansion_node(t_node **n)
{
	(*n)->type = 1;
	(*n)->left_node = malloc(sizeof(t_node));
	ft_memset((*n)->left_node, 0, sizeof(t_node));
	(*n)->left_node->value = ft_strdup((*n)->value);
	ft_free((*n)->value);
	(*n)->left_node->id = "RAW";
	(*n)->left_node->type = 0;
	(*n)->right_node = add_expansions((*n)->left_node);
}

int	visit(t_node *node, size_t run)
{
	static int	i;

	if (!i || !run)
		i = 0;
	if (node->type == 1)
	{
		visit(node->left_node, run + 1);
		visit(node->right_node, run + 1);
		if (ft_strncmp(node->id, "PIPE", 4) == 0)
			i++;
	}
	if (node->type == 2)
	{
		printf("%s: %s\n", node->id, node->value);
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(node->value, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	return (i);
}
