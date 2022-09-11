/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:06:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 20:13:44 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
