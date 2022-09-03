/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/02 14:17:02 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * empty file to include addtl functions *//

int	check_io(char *prev, char *current)
{
	return (((ft_strncmp(prev, DGREAT, 2) == 0
				|| ft_strncmp(prev, GREAT, 1) == 0)
			&& ((ft_strncmp(current, DLESS, 2) == 0)
				|| (ft_strncmp(current, LESS, 1) == 0)))
		|| ((ft_strncmp(prev, DLESS, 2) == 0
				|| ft_strncmp(prev, LESS, 1) == 0)
			&& ((ft_strncmp(current, DGREAT, 2) == 0)
				|| (ft_strncmp(current, GREAT, 1) == 0))));
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
