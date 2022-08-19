/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:21:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/19 20:01:44 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirs	redir(char *op, char *fname)
{
	t_redirs	rd;
	
	init_rd(&rd);
	if (ft_strncmp(op, ">>", 2) == 0) //operator
	{
		rd.append = fname;
		rd.lastout = 'a';
	}
	else if (ft_strncmp(op, ">", 1) == 0) //operator
	{
		rd.outfile = fname;
		rd.lastout = 'o';
	}
	else if (ft_strncmp(op, "<<", 2) == 0) //operator
	{
		rd.infile = fname;
		rd.lastin = 'i';
	}
	else if (ft_strncmp(op, "<", 1) == 0) //operator
	{
		rd.heredoc = fname;
		rd.lastin = 'h';
	}
	return (rd);
}

//can be used for next intermediate representation(IR)
//and place all the necessary into structs for
//further processing/execution
// never returns - executes all commands
void traverse(t_node *root, int count, t_data *data)
{
	// char		*ID;
	t_node		*current;
	t_pipe		**p;
	char		*cmd;
	char		*fname;
	char		*op;
	t_redirs	rd;
	int			i;

	current = root;
	if (strcmp(current->id, "PIPELINE") == 0)
	{
		i = 0;
		p = malloc(sizeof(t_pipe *) * (count + 1));
		while (strcmp(current->id, "PIPELINE") == 0)
		{
			p[i] = malloc(sizeof(t_pipe));
			if (current->left_node->type == 0)
			{
				p[i]->fcmd = ft_strdup(current->left_node->value);
				printf("p[%d] :%s\n", i, p[i]->fcmd);
			}
			if (current->left_node->type == 1)
			{
				p[i]->fcmd = ft_strdup(current->left_node->left_node->value);
				printf("p[%d] :%s\n", i, p[i]->fcmd);
				op = ft_strdup(current->left_node->right_node->left_node->value);
				fname = ft_strdup(current->left_node->right_node->right_node->value);
				printf("op: %s, fname: %s\n", op, fname);
				p[i]->rd = redir(op, fname);
			}
			current = current->right_node;
			i++;
		}
		p[i] = malloc(sizeof(t_pipe));
		if (current->type == 0)
		{
			p[i]->fcmd = ft_strdup(current->value);
			printf("p[%d] :%s\n", i, p[i]->fcmd);
		}
		if (current->type == 1)
		{
			p[i]->fcmd = ft_strdup(current->left_node->value);
			printf("p[%d] :%s\n", i, p[i]->fcmd);
			op = ft_strdup(current->right_node->left_node->value);
			fname = ft_strdup(current->right_node->right_node->value);
			p[i]->rd = redir(op, fname);
		}
		p[0]->nchild = count + 1;
		printf("nchild: %d\n", p[0]->nchild);
		p[0]->data = data;
		pipes(p);
	}
	else if (strcmp(current->id, "COMMAND") == 0)
	{
		if (current->type == 0)
		{
			master_execute(current->value, data);
		}
		else 
		{
			cmd = ft_strdup(current->left_node->value); //command
			fname = ft_strdup(current->right_node->right_node->value); //fname
			op = ft_strdup(current->right_node->left_node->value); //op
			rd = redir(op, fname);
			create_file(cmd, &rd, data);
		}
	}
}