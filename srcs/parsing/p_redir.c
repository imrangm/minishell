/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/12 10:48:55 by imustafa         ###   ########.fr       */
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
	else if (ft_strlen(lf) == 2 && lf[0] == LESS
		&& ft_strlen(current) == 1 && current[0] == LESS)
		ft_readline(rt);
	else if (ft_strlen(lf) == 1 && lf[0] == LESS
		&& ft_strlen(current) == 2 && current[0] == LESS)
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
		rd->lastout = O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC;
	}
	else if (ft_strncmp(op, ">", 1) == 0)
	{
		rd->outfile = fname;
		rd->lastout = O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC;
	}
	else if (ft_strncmp(op, "<<", 2) == 0)
	{
		rd->heredoc = fname;
		rd->lastin = O_CREAT | O_RDWR | O_TRUNC;
	}
	else if (ft_strncmp(op, "<", 1) == 0)
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
