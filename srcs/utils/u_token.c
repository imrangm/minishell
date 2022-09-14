/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:02:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/14 08:59:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token(t_token *tokens)
{
	tokens->type = 0;
	tokens->value = NULL;
	tokens->space = 0;
}

void	init_toklist(t_toklist *tokens)
{
	tokens->first = NULL;
	tokens->current = NULL;
	tokens->count = 0;
	tokens->id = 0;
}

int	count_tokens(t_token *tok)
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
