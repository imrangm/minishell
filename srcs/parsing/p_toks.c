/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_toks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:15:30 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 02:06:13 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_toklist(t_toklist *tokens)
{
	tokens->first = NULL;
	tokens->current = NULL;
	tokens->count = 0;
	tokens->id = 0;
}

char	*current_token(t_toklist *toks)
{
	return (toks->current->value);
}

int	has_more_tokens(t_toklist *toks)
{
	if (!toks->current)
		return (1);
	else if (toks->current->next)
		return (1);
	else
		return (0);
}

int	look_ahead(t_toklist *toks)
{
	if (!toks->current)
		return (toks->first->type);
	else if (toks->current->next)
		return (toks->current->next->type);
	else
		return (0);
}

void	next_token(t_toklist *toks)
{
	if (!toks->current)
		toks->current = toks->first;
	else if (has_more_tokens(toks))
		toks->current = toks->current->next;
}
