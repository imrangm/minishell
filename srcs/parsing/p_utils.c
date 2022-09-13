/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 15:31:27 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * empty file to include addtl functions *//

int	check_io(char *prev, char *current)
{
	return ((prev[0] == GREAT && current[0] == LESS)
		|| (prev[0] == LESS && current[0] == GREAT));
}

int	check_error(t_node *node, t_data *data)
{
	if (node->type == 1)
	{
		check_error(node->left_node, data);
		check_error(node->right_node, data);
	}
	else if (node->type == 2)
	{
		ft_putstr_fd(node->value, 2);
		ft_putchar_fd('\n', 2);
		data->last_exit_status = 1;
		data->error = 1;
		return (1);
	}
	return (0);
}

int	count_tokens(t_scan *src)
{
	int	i;
	int	t;
	int	count;
	int	q;
	int	nq;

	i = 0;
	t = src->chars[i]->t;
	count = 0;
	q = 0;
	nq = 0;
	while (i < src->len)
	{
		if (ft_isquote(src->chars[i]->c) && !q)
		{
			q = src->chars[i]->c;
			if (nq && nq == q)
			{
				nq = 0;
				count++;
			}
		}
		else if (q == src->chars[i]->c)
		{
			nq = q;
			q = 0;
		}
		if (src->chars[i]->t != t)
		{
			t = src->chars[i]->t;
			while (!t)
				continue ;
			count++;
		}
		i++;
	}
	printf("count: %d\n", count);
	return (count);
}
