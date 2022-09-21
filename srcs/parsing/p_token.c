/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:50:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 14:23:27 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token(t_token *tokens)
{
	tokens->type = 0;
	tokens->value = NULL;
	tokens->space = 0;
	tokens->exp = 1;
}

int	ctoks(t_token *tok)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tok;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
