/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/28 11:59:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_more_tokens(t_token **toks)
{
	return ((toks[0]->iter + 1) < toks[0]->count);
}

int	look_ahead(t_token **toks)
{
	t_token	ret;
	int		i;

	ret.value = 0;
	ret.type = 0;
	if (!has_more_tokens(toks))
		return (ret.type);
	if (!toks[0]->cur)
		return (toks[0]->type);
	i = toks[0]->iter;
	ret = *toks[i + 1];
	return (ret.type);
}

char	*current_token(t_token **toks)
{
	return (toks[toks[0]->iter]->value);
}

void	next_token(t_token **toks)
{
	if (toks[0]->cur && has_more_tokens(toks))
	{
		toks[0]->iter++;
	}
	if (!toks[0]->iter && has_more_tokens(toks))
	{
		toks[0]->iter = 0;
		toks[0]->cur = 1;
	}
}

t_node	*parse(t_token **toks)
{	
	set_signalset(1);
	if (look_ahead(toks) == PIPE)
	{
		return (error_node(ft_strjoin("unexpected token near: ",
					current_token(toks))));
	}
	return (parse_pipeline(toks));
}
