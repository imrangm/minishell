/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/16 11:30:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_redirection(t_node **left, t_node **right, char *current)
{
	char	*lf;
	char	*rt;

	lf = (*left)->value;
	rt = (*right)->value;
	if (lf[0] == GREAT)
		empty_file(rt);
	else if (op_type(lf) == DLESS && op_type(current) == LESS)
		ft_readline(rt);
	else if (op_type(lf) == LESS && op_type(current) == DLESS)
	{
		if (access(rt, F_OK) == -1)
		{
			ft_free(*right);
			*right = error_node(ft_strjoin_and_free(rt,
						" : No such file or directory"));
			return (-1);
		}
	}
	return (1);
}

t_node	*parse_redirection(t_toklist *toks)
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

t_node	*parse_io(t_node *redir, t_toklist *toks, char *id)
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
	char	type;

	type = op_type(op);
	if (type == DGREAT)
	{
		rd->append = fname;
		rd->lastout = O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC;
	}
	else if (type == GREAT)
	{
		rd->outfile = fname;
		rd->lastout = O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC;
	}
	else if (type == DLESS)
	{
		rd->heredoc = fname;
		rd->lastin = O_CREAT | O_RDWR | O_TRUNC;
	}
	else if (type == LESS)
	{
		rd->infile = fname;
		rd->lastin = O_RDONLY | O_CLOEXEC;
	}
}

t_redirs	get_redir(t_node *rd)
{
	char		*fname;
	char		*fname_io;
	char		*op;
	char		*op_io;
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
		fname = rd->left_node->right_node->value;
		add_redir(&redirs, op, fname);
		op_io = rd->right_node->left_node->value;
		fname_io = rd->right_node->right_node->value;
		add_redir(&redirs, op_io, fname_io);
	}
	return (redirs);
}
