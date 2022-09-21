/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:48:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 15:50:37 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	determine_dgreat(t_redirs *rd, char *fname)
{
	if (access(fname, F_OK))
		rd->lastout = O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC;
	else
		rd->lastout = O_RDWR | O_APPEND | O_CLOEXEC;
}

void	add_redir(t_redirs *rd, char *op, char *fname)
{
	char	type;

	type = op_type(op);
	if (type == DGREAT)
	{
		rd->append = fname;
		determine_dgreat(rd, fname);
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
