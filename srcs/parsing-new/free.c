/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:27:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/19 10:44:33 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
to contain all free functions
*/
void	free_chars(t_type **chars, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(chars[i]);
		chars[i] = NULL;
		i++;
	}
	free(chars);
}

void	free_tokens(t_token **toks)
{
	int	i;
	int	n;

	i = 0;
	n = toks[0]->count;
	while (i < n)
	{
		ft_free(toks[i]->value);
		ft_free(toks[i]);
		i++;
	}
	ft_free(toks);
}

void	free_node(t_node *node)
{
	// printf("freed id: %s, value: %s\n", node->id, node->value);
	ft_free(node->id);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
}

void	free_nodes(t_node *root)
{
	if (root->type == 0)
	{
		free_node(root);
	}
	if (root->type == 1)
	{
		free_nodes(root->left_node);
		free_nodes(root->right_node);
	}
	if (root->type == 2)
	{
		free_node(root);
	}
}