/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_AST.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:19:39 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 15:16:22 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_io(t_node **n, t_toklist *toks)
{
	int		pr_l;
	int		pr_r;

	pr_r = process_redirection(&(*n)->right->left,
			&(*n)->right->right,
			current_token(toks));
	if (pr_r == -1)
		return ;
	pr_l = process_redirection(&(*n)->left->left,
			&(*n)->left->right,
			current_token(toks));
	if (pr_l == -1)
		return ;
	if (pr_r)
	{
		free_pair((*n)->right->left, (*n)->right->right);
		ft_free((*n)->right);
		(*n)->right = parse_redirection(toks, "IO");
	}
	if (pr_l)
	{
		free_pair((*n)->left->left, (*n)->left->right);
		ft_free((*n)->left);
		(*n)->left = parse_redirection(toks, "IO");
	}
}

void	u_check_io(t_node **n, t_toklist *toks, int *io)
{
	if (check_io((*n)->left->value, current_token(toks)))
	{
		(*n)->id = "IO";
		(*n) = parse_io((*n), toks);
	}
	if ((*n)->right && (*n)->right->type == 1)
		*io = 1;
}
