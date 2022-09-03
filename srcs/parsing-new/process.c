/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/03 11:17:29 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//left and right have same arg and code, can be reduced to 1 function
void	process_pipe_left(t_node *n, t_pipe ***p, t_data *data, int *i)
{
	if (n->type == 1
		&& n->left_node->type == 1)
	{
		expander(n->left_node, data);
		(*p)[*i]->fcmd = n->left_node->value;
		(*p)[*i]->rd = get_redir(n->right_node);
	}
	if (n->type == 1
		&& n->left_node->type == 0)
	{
		if (ft_strncmp(n->left_node->id, "RAW", 3) == 0)
		{
			expander(n, data);
			(*p)[*i]->fcmd = n->left_node->value;
		}
		if (ft_strncmp(n->left_node->id, "ARGS", 3) == 0)
		{
			(*p)[*i]->fcmd = n->left_node->value;
			(*p)[*i]->rd = get_redir(n->right_node);
		}
	}
}

void	process_pipe_right(t_node *n, t_data *data, t_pipe ***p, int i)
{
	if (n->type == 1 && n->left_node->type == 1)
	{
		expander(n->left_node, data);
		(*p)[i]->fcmd = ft_strdup(n->left_node->left_node->value);
		(*p)[i]->rd = get_redir(n->right_node);
	}
	if (n->type == 1 && n->left_node->type == 0)
	{
		if (ft_strncmp(n->left_node->id, "RAW", 3) == 0)
		{
			expander(n, data);
			(*p)[i]->fcmd = n->left_node->value;
		}
		if (ft_strncmp(n->left_node->id, "ARGS", 3) == 0)
		{
			(*p)[i]->fcmd = n->left_node->left_node->value;
			(*p)[i]->rd = get_redir(n->right_node);
		}
	}
}

void	process_pipe(t_node *n, t_pipe ***p, t_data *data)
{
	int	i;

	i = 0;
	while (ft_strncmp(n->id, "PIPE", 4) == 0)
	{
		(*p)[i] = malloc(sizeof(t_pipe));
		init_rd(&(*p)[i]->rd);
		if (n->left_node->type == 0)
		{
			(*p)[i]->fcmd = n->left_node->value;
		}
		else
			process_pipe_left(n->left_node, p, data, &i);
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
		process_pipe_right(n, data, p, i);
}

void	process_command(t_node *n, t_data *data)
{
	char		*cmd;
	t_redirs	rd;

	if (n->type == 1 && n->left_node->type == 0)
	{
		if (ft_strncmp(n->left_node->id, "RAW", 3) == 0)
		{
			expander(n, data);
			master_execute(n->left_node->value, data);
		}
		else
		{
			cmd = n->left_node->value;
			rd = get_redir(n->right_node);
			create_file(cmd, &rd, data);
		}
	}
	if (n->type == 1 && n->left_node->type == 1)
	{
		expander(n->left_node, data);
		cmd = n->left_node->left_node->value;
		rd = get_redir(n->right_node);
		create_file(cmd, &rd, data);
	}
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
		process_pipe(current, &p, data);
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
