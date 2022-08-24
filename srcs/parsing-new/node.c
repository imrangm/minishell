/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:06:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/24 08:19:18 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*node(t_token **toks)
{
	t_node	*word;
	int		i;

	i = toks[0]->iter;
	word = malloc(sizeof(t_node));
	ft_memset(word, 0, sizeof(t_node));
	word->type = 0;
	word->value = ft_strdup(toks[i]->value);
	return (word);
}

t_node	*pair_node(t_node *left, t_node *right, char *id)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	ft_memset(new, 0, sizeof(t_node));
	new->id = ft_strdup(id);
	new->type = 1;
	new->left_node = left;
	new->right_node = right;
	return (new);
}

t_node	*error_node(char *msg)
{
	t_node	*err;

	err = malloc(sizeof(t_node));
	err->value = (msg);
	err->type = 2;
	err->id = ft_strdup("ERROR");
	return (err);
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
