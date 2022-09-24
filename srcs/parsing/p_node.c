/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:06:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:35 by nmadi            ###   ########.fr       */
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
	new->left = left;
	new->right = right;
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
