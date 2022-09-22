/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:42 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/22 14:17:52 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_infile(t_node **left, t_node **right, char *current)
{
	char	*lf;
	char	*rt;
	int		type;

	lf = (*left)->value;
	rt = (*right)->value;
	type = op_type(lf);
	if (type == DLESS && current[0] == LESS)
	{
		ft_readline(rt);
		return (1);
	}
	if (type == LESS && current[0] == LESS)
	{
		if (access(rt, F_OK) == -1)
		{
			ft_free(*right);
			*right = error_node(ft_strjoin_and_free(rt,
						" : No such file or directory"));
			return (-1);
		}
		else
			return (1);
	}
	return (0);
}

int	process_outfile(t_node **left, t_node **right, char *current)
{
	char	*lf;
	char	*rt;
	int		type;

	lf = (*left)->value;
	rt = (*right)->value;
	type = op_type(lf);
	if (type == DGREAT && current[0] == GREAT && access(rt, F_OK))
	{
		empty_file(rt);
		return (1);
	}
	if (type == DGREAT && current[0] == GREAT)
		return (1);
	if (type == GREAT && current[0] == GREAT)
	{
		empty_file(rt);
		return (1);
	}
	return (0);
}

int	process_redirection(t_node **left, t_node **right, char *current)
{
	if ((*left)->type == 2 || (*right)->type == 2)
		return (-1);
	if (process_infile(left, right, current))
		return (1);
	if (process_outfile(left, right, current))
		return (1);
	return (0);
}

t_node	*parse_redirection(t_toklist *toks, char *id)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	ft_memset(left, 0, sizeof(t_node));
	ft_memset(right, 0, sizeof(t_node));
	left->value = ft_strdup(current_token(toks));
	left->id = "OP";
	if (look_ahead(toks) != WORD && look_ahead(toks) != SQUOTE
		&& look_ahead(toks) != DQUOTE)
	{
		ft_free(right);
		right = error_node(ft_strjoin("unexpected token near: ",
					current_token(toks)));
		return (pair_node(left, right, id));
	}
	next_token(toks);
	if (!ft_strlen(current_token(toks)))
	{
		ft_free(right);
		right = error_node(ft_strjoin("File name missing",
					current_token(toks)));
		return (pair_node(left, right, id));
	}
	right->value = ft_strdup(current_token(toks));
	right->id = "FILE";
	return (pair_node(left, right, id));
}

t_node	*parse_io(t_node *redir, t_toklist *toks)
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
	if (!ft_strlen(current_token(toks)))
	{
		ft_free(right);
		right = error_node(ft_strjoin("File name missing",
					current_token(toks)));
		return (pair_node(left, right, "IO"));
	}
	right->value = ft_strdup(current_token(toks));
	right->id = "FILE";
	pair_left = pair_node(left, right, "IO");
	return (pair_node(pair_left, redir, "REDIR"));
}
