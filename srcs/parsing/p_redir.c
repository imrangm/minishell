/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 14:54:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_redirection(t_node **left, t_node **right, char *current)
{
	char	*lf;
	char	*rt;

	lf = (*left)->value;
	rt = (*right)->value;
	if (op_type(lf) == DGREAT && access(rt, F_OK))
		empty_file(rt);
	else if (op_type(lf) == GREAT)
		empty_file(rt);
	else if (op_type(lf) == DLESS && current[0] == LESS)
		ft_readline(rt);
	else if (op_type(lf) == LESS && current[0] == LESS)
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
		ft_free(right);
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
		if (access(fname, F_OK))
			rd->lastout = O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC;
		else
			rd->lastout = O_RDWR | O_APPEND | O_CLOEXEC;
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
	if (rd->left->type == 0)
	{
		op = rd->left->value;
		fname = rd->right->value;
		add_redir(&redirs, op, fname);
	}
	if (rd->left->type == 1)
	{
		op = rd->left->left->value;
		fname = rd->left->right->value;
		add_redir(&redirs, op, fname);
		op_io = rd->right->left->value;
		fname_io = rd->right->right->value;
		add_redir(&redirs, op_io, fname_io);
	}
	return (redirs);
}
