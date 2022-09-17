/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/17 16:35:19 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* PROCESSING TREE*/
static void	process_pipe_left(t_node *n, t_pipe ***p, int *i)
{
	(*p)[*i]->fcmd = n->left->value;
	(*p)[*i]->rd = get_redir(n->right);
}

static void	process_pipe_right(t_node *n, t_pipe ***p, int i)
{
	(*p)[i]->fcmd = n->left->value;
	(*p)[i]->rd = get_redir(n->right);
}

static t_cmd	*process_pipe(t_node *n, t_pipe ***p, int nchild)
{
	int	i;

	i = 0;
	while (ft_strncmp(n->id, "PIPE", 4) == 0)
	{
		(*p)[i] = malloc(sizeof(t_pipe));
		init_rd(&(*p)[i]->rd);
		if (n->left->type == 0)
			(*p)[i]->fcmd = n->left->value;
		else
			process_pipe_left(n->left, p, &i);
		n = n->right;
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
	return ((t_cmd *) pipe_cmd(*p, nchild));
}

static t_cmd	*process_redir(t_node *n)
{
	char		*cmd;
	t_redirs	rd;

	init_rd(&rd);
	cmd = n->left->value;
	rd = get_redir(n->right);
	return ((t_cmd *) redir_cmd(cmd, &rd));
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
		cmd = process_pipe(current, &p, count + 1);
		p[0]->nchild = count + 1;
		p[0]->data = data;
	}
	else
	{
		if (current->type == 0)
			cmd = (t_cmd *) exe_cmd(current->value);
		else
			cmd = process_redir(current);
	}
	return (cmd);
}
