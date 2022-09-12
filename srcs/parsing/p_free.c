/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:27:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 20:15:12 by imustafa         ###   ########.fr       */
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
	ft_free(node->value);
	ft_free(node);
}

void	free_nodes(t_node *root)
{
	if (root && root->type == 0)
	{
		free_node(root);
	}
	else if (root && root->type == 1)
	{
		free_nodes(root->left_node);
		free_nodes(root->right_node);
		ft_free(root);
	}
	else if (root && root->type == 2)
	{
		free_node(root);
	}
}

void	free_pair(t_node *left, t_node *right)
{
	ft_free(left->value);
	ft_free(left);
	ft_free(right->value);
	ft_free(right);
}