/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/12 11:03:26 by imustafa         ###   ########.fr       */
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

static void	init_(int *i, int *t, int *count, t_scan *src)
{
	*i = 0;
	*t = src->chars[*i]->t;
	*count = 1;
}

static void	handle_quote(t_scan *src, int *q, int *i, int *count)
{
	*q = src->chars[*i]->c;
	(*count)++;
}

int	count_tokens(t_scan *src)
{
	int	i;
	int	t;
	int	count;
	int	q;

	init_(&i, &t, &count, src);
	q = 0;
	while (i < src->len)
	{
		if (ft_isquote(src->chars[i]->c) && !q)
			handle_quote(src, &q, &i, &count);
		else if (q == src->chars[i]->c)
			q = 0;
		else if (src->chars[i]->t != t && src->chars[i]->t != SQUOTE
			&& src->chars[i]->t != DQUOTE)
		{
			t = src->chars[i]->t;
			if (!t)
				continue ;
			count++;
		}
		i++;
	}
	return (count);
}
