/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:02:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 20:46:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token(t_token *tokens)
{
	tokens->type = 0;
	tokens->value = NULL;
	tokens->iter = 0;
	tokens->cur = 0;
	tokens->count = 0;
	tokens->quote = 0;
	tokens->space = 0;
	tokens->first = 0;
}

int	count_tokens_ll(t_token *tok)
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
