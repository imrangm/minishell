/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/20 03:10:01 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_readline(char *lim)
{
	char	*text;

	text = read_line(lim);
	free(text);
}

int	check_io(char *prev, char *current)
{
	return ((prev[0] == GREAT && current[0] == LESS)
		|| (prev[0] == LESS && current[0] == GREAT));
}

int	check_error(t_node *node, t_data *data)
{
	if (node->type == 1)
	{
		check_error(node->left, data);
		check_error(node->right, data);
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

char	op_type(char *op)
{
	if (ft_strlen(op) == 2 && op[0] == LESS)
		return (DLESS);
	if (ft_strlen(op) == 2 && op[0] == GREAT)
		return (DGREAT);
	if (ft_strlen(op) == 1 && op[0] == LESS)
		return (LESS);
	if (ft_strlen(op) == 1 && op[0] == GREAT)
		return (GREAT);
	if (ft_strlen(op) == 1 && op[0] == LINE)
		return (LINE);
	return (0);
}

void	free_redirs(t_redircmd *redir)
{
	t_data	*data;

	data = redir->data;
	ft_free(redir);
	free_data(data);
	free_nodes(data->root);
	exit(data->last_exit_status);
}
