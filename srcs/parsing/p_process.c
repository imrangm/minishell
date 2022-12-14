/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:38 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipe_redir(t_node *n, t_pipe ***p, int i)
{
	if (ft_strcmp(n->id, "REDIR") == 0)
	{
		(*p)[i]->fcmd = NULL;
		(*p)[i]->rd = get_redir(n);
	}
	else
	{
		(*p)[i]->fcmd = n->left->value;
		(*p)[i]->rd = get_redir(n->right);
	}
}

static void	create_pipe(t_node *n, t_pipe ***p, int i)
{
	(*p)[i] = malloc(sizeof(t_pipe));
	init_rd(&(*p)[i]->rd);
	if (n->type == 0)
		(*p)[i]->fcmd = n->value;
	else
		pipe_redir(n, p, i);
}

static t_cmd	*process_pipe(t_node *n, t_pipe ***p, int nchild, t_data *data)
{
	int	i;

	i = 0;
	while (ft_strncmp(n->id, "PIPE", 4) == 0)
	{
		create_pipe(n->left, p, i);
		n = n->right;
		i++;
	}
	create_pipe(n, p, i);
	return ((t_cmd *) pipe_cmd(*p, nchild, data));
}

static t_cmd	*process_redir(t_node *n, t_data *data)
{
	char		*cmd;
	t_redirs	rd;

	init_rd(&rd);
	if (ft_strcmp(n->id, "REDIR") == 0)
	{
		cmd = NULL;
		rd = get_redir(n);
	}
	else
	{
		cmd = n->left->value;
		rd = get_redir(n->right);
	}
	return ((t_cmd *) redir_cmd(cmd, &rd, data));
}

t_cmd	*process_command(t_node *root, int count, t_data *data)
{
	t_node		*current;
	t_pipe		**p;
	t_cmd		*cmd;

	current = root;
	data->root = root;
	if (count)
	{
		p = malloc(sizeof(t_pipe *) * (count + 1));
		cmd = process_pipe(current, &p, count + 1, data);
	}
	else if (current->type == 1)
		cmd = process_redir(current, data);
	else
		cmd = (t_cmd *) exec_cmd(current->value, data);
	return (cmd);
}
