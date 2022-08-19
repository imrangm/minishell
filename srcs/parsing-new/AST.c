/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:00:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/19 17:21:51 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*node(t_token **toks)
{
	t_node	*word;
	int		i;

	i = toks[0]->iter;
	word = malloc(sizeof(t_node));
	word->type = 0;
	word->value = ft_strdup(toks[i]->value);
	return (word);
}

t_node	*pair_node(t_node *left, t_node *right, char *id)
{
	t_node	*new;
	int		len;

	len = ft_strlen(id) + 1;
	new = malloc(sizeof(t_node));
	new->id = malloc(sizeof(char) * len);
	new->id = id;
	new->type = 1;
	new->left_node = left;
	new->right_node = right;
	return (new);
}

t_node	*error_node(char *msg)
{
	// store error encountered
	// type should be 2
	// display only after building the whole tree
	t_node	*err;

	err = malloc(sizeof(t_node));
	err->value = (msg);
	err->type = 2;
	err->id = "ERROR";
	return (err);
}

void	indent(size_t spaces)
{
	size_t	i;

	i = 0;
	while (i < spaces)
	{
		printf(" ");
		i++;
	}
}

int	visit(t_node *node, size_t spaces)
{
	static int	i;
	
	indent(spaces);
	if (!i || !spaces)
		i = 0;
	if (node->type == 0)
	{
		if (ft_strncmp(node->id, "START", 5) == 0
			|| ft_strncmp(node->id, "END", 3) == 0)
			printf("%s: %d\n", node->id, node->val);
		else
			printf("%s: %s\n", node->id, node->value);
	}
	if (node->type == 1)
	{
		printf("%s:\n", node->id);
		visit(node->left_node, spaces + 3);
		visit(node->right_node, spaces + 3);
		if (strcmp(node->id, "PIPELINE") == 0)
			i++;
	}
	if (node->type == 2)
	{
		printf("%s: %s\n", node->id, node->value);
	}
	return (i);
}

void	test_ast(void)
{
	return ;
}