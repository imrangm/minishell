/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/30 03:05:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_redirection(t_node **left, t_node **right)
{
	char	*lf;
	char	*rt;

	lf = (*left)->value;
	rt = (*right)->value;
	if (ft_strncmp(lf, DGREAT, 2) == 0)
		empty_file(rt);
	if (ft_strncmp(lf, GREAT, 1) == 0)
		empty_file(rt);
	if (ft_strncmp(lf, DLESS, 2) == 0)
		read_line(rt);
	if (ft_strncmp(lf, LESS, 1) == 0)
	{
		if (access(rt, F_OK))
		{
			ft_free(*right);
			*right = error_node(ft_strjoin_and_free(rt,
						" : No such file or directory"));
			return (-1);
		}
	}
	return (1);
}

t_node	*parse_redirection(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	left->value = ft_strdup(current_token(toks));
	left->id = "OP";
	if (look_ahead(toks) != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
					current_token(toks)));
		return (pair_node(left, right, "REDIR"));
	}
	next_token(toks);
	right->value = ft_strdup(current_token(toks));
	right->id = "FILE";
	return (pair_node(left, right, "REDIR"));
}

t_node	*parse_io(t_node *redir, t_token **toks, char *id)
{
	t_node	*left;
	t_node	*right;
	t_node	*pair_left;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	left->value = ft_strdup(current_token(toks));
	left->id = "OP";
	if (look_ahead(toks) != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
					current_token(toks)));
		return (pair_node(left, right, "IO"));
	}
	next_token(toks);
	right->value = ft_strdup(current_token(toks));
	right->id = "FILE";
	pair_left = pair_node(left, right, id);
	return (pair_node(pair_left, redir, "REDIR"));
}

void	add_redir(t_redirs *rd, char *op, char *fname)
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
	char		*fname_in;
	char		*fname_out;
	char		*op;
	t_redirs	redirs;

	init_rd(&redirs);
	if (rd->left_node->type == 0)
	{
		op = rd->left_node->value;
		fname = rd->right_node->value;
		add_redir(&redirs, op, fname);
	}
	if (rd->left_node->type == 1)
	{
		op = rd->left_node->left_node->value;
		fname_in = rd->left_node->right_node->value;
		add_redir(&redirs, op, fname_in);
		op = rd->right_node->left_node->value;
		fname_out = rd->right_node->right_node->value;
		add_redir(&redirs, op, fname_out);
	}
	return (redirs);
}
