/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 20:23:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_pipe_left(t_node *n, t_pipe ***p, int *i)
{
	(*p)[*i]->fcmd = n->left_node->value;
	(*p)[*i]->rd = get_redir(n->right_node);
}

void	process_pipe_right(t_node *n, t_pipe ***p, int i)
{
	(*p)[i]->fcmd = n->left_node->value;
	(*p)[i]->rd = get_redir(n->right_node);
}

void	process_pipe(t_node *n, t_pipe ***p)
{
	int	i;

	i = 0;
	while (ft_strncmp(n->id, "PIPE", 4) == 0)
	{
		(*p)[i] = malloc(sizeof(t_pipe));
		init_rd(&(*p)[i]->rd);
		if (n->left_node->type == 0)
			(*p)[i]->fcmd = n->left_node->value;
		else
			process_pipe_left(n->left_node, p, &i);
		n = n->right_node;
		i++;
	}
	(*p)[i] = malloc(sizeof(t_pipe));
	if (n->type == 0)
	{
		(*p)[i]->fcmd = n->value;
		init_rd(&(*p)[i]->rd);
	}
	else
		process_pipe_right(n, p, i);
}

void	process_command(t_node *n, t_data *data)
{
	char		*cmd;
	t_redirs	rd;

	init_rd(&rd);
	cmd = n->left_node->value;
	rd = get_redir(n->right_node);
	create_file(cmd, &rd, data);
}

void	process_tree(t_node *root, int count, t_data *data)
{
	t_node		*current;
	t_pipe		**p;

	current = root;
	data->root = root;
	if (ft_strncmp(current->id, "PIPE", 4) == 0)
	{
		p = malloc(sizeof(t_pipe *) * (count + 1));
		process_pipe(current, &p);
		p[0]->nchild = count + 1;
		p[0]->data = data;
		pipes(p);
	}
	else if (ft_strncmp(current->id, "COMM", 4) == 0)
	{
		if (current->type == 0)
			master_execute(current->value, data);
		else
			process_command(current, data);
	}
}
