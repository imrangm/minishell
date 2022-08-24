/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/24 08:15:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir(t_redirs *rd, char *op, char *fname)
{
	if (ft_strncmp(op, ">>", 2) == 0)
	{
		rd->append = fname;
		rd->lastout = 'a';
	}
	else if (ft_strncmp(op, ">", 1) == 0)
	{
		rd->outfile = fname;
		rd->lastout = 'o';
	}
	else if (ft_strncmp(op, "<<", 2) == 0)
	{
		rd->heredoc = fname;
		rd->lastin = 'h';
	}
	else if (ft_strncmp(op, "<", 1) == 0)
	{
		rd->infile = fname;
		rd->lastin = 'i';
	}
}

t_redirs	get_redir(t_node *rd)
{
	char		*fname;
	char		*op;
	t_redirs	redirs;

	init_rd(&redirs);
	if (rd->left_node->type == 0)
	{
		op = ft_strdup(rd->left_node->value);
		fname = ft_strdup(rd->right_node->value);
		printf("op: %s, fname: %s\n", op, fname);
		redir(&redirs, op, fname);
	}
	if (rd->left_node->type == 1)
	{
		op = ft_strdup(rd->left_node->left_node->value);
		fname = ft_strdup(rd->left_node->right_node->value);
		redir(&redirs, op, fname);
		op = ft_strdup(rd->right_node->left_node->value);
		fname = ft_strdup(rd->right_node->right_node->value);
		redir(&redirs, op, fname);
	}
	return (redirs);
}

void traverse(t_node *root, int count, t_data *data)
{
	t_node		*current;
	t_pipe		**p;
	char		*cmd;
	t_redirs	rd;
	int			i;

	current = root;
	if (ft_strncmp(current->id, "PIPE", 4) == 0)
	{
		i = 0;
		p = malloc(sizeof(t_pipe *) * (count + 1));
		while (ft_strncmp(current->id, "PIPE", 4) == 0)
		{
			p[i] = malloc(sizeof(t_pipe));
			if (current->left_node->type == 0)
			{
				p[i]->fcmd = ft_strdup(current->left_node->value);
				printf("p[%d] :%s\n", i, p[i]->fcmd);
			}
			if (current->left_node->type == 1
				&& current->left_node->left_node->type == 1)
			{
					expander(current->left_node->left_node, data);
					p[i]->fcmd = ft_strdup(current->left_node->left_node->left_node->value);
					p[i]->rd = get_redir(current->left_node->right_node);
					printf("p[%d] :%s\n", i, p[i]->fcmd);
			}
			if (current->left_node->type == 1
				&& current->left_node->left_node->type == 0)
			{
				if (ft_strncmp(current->left_node->left_node->id, "RAW", 3) == 0)
				{
					expander(current->left_node, data);
					p[i]->fcmd = ft_strdup(current->left_node->left_node->value);
				}
				if (ft_strncmp(current->left_node->left_node->id, "ARGS", 3) == 0)
				{
					expander(current->left_node->left_node->left_node, data);
					p[i]->fcmd = ft_strdup(current->left_node->left_node->left_node->value);
					p[i]->rd = get_redir(current->left_node->right_node);
				}
				printf("p[%d] :%s\n", i, p[i]->fcmd);
			}
			current = current->right_node;
			i++;
		}
		p[i] = malloc(sizeof(t_pipe));
		printf("HERE2\n");
		if (current->type == 0)
		{
			p[i]->fcmd = ft_strdup(current->value);
			printf("p[%d] :%s\n", i, p[i]->fcmd);
		}
		if (current->type == 1 && current->left_node->type == 1)
		{
			expander(current->left_node, data);
			p[i]->fcmd = ft_strdup(current->left_node->left_node->value);
			printf("p[%d] :%s\n", i, p[i]->fcmd);
			p[i]->rd = get_redir(current->right_node);
		}
		if (current->type == 1 && current->left_node->type == 0)
		{
			if (ft_strncmp(current->left_node->id, "RAW", 3) == 0)
			{
				expander(current, data);
				p[i]->fcmd = ft_strdup(current->left_node->value);
			}
			if (ft_strncmp(current->left_node->id, "ARGS", 3) == 0)
			{
				expander(current->left_node, data);
				p[i]->fcmd = ft_strdup(current->left_node->left_node->value);
				p[i]->rd = get_redir(current->right_node);
			} 
			printf("p[%d] :%s\n", i, p[i]->fcmd);
		}
		p[0]->nchild = count + 1;
		printf("nchild: %d\n", p[0]->nchild);
		p[0]->data = data;
		pipes(p);
	}
	else if (ft_strncmp(current->id, "C", 1) == 0)
	{
		if (current->type == 0)
		{
			master_execute(current->value, data);
		}
		if (current->type == 1 && current->left_node->type == 0)
		{
			if (ft_strncmp(current->left_node->id, "RAW", 3) == 0)
			{
				expander(current, data);
				master_execute(current->left_node->value, data);
			}
			else
			{
				cmd = ft_strdup(current->left_node->value);
				rd = get_redir(current->right_node);
				create_file(cmd, &rd, data);
			}
		}
		if (current->type == 1 && current->left_node->type == 1)
		{
			expander(current->left_node, data);
			cmd = ft_strdup(current->left_node->left_node->value);
			rd = get_redir(current->right_node);
			create_file(cmd, &rd, data);
		}
	}
}