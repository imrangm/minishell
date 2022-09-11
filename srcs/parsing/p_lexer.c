/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:07:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 11:00:28 by imustafa         ###   ########.fr       */
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
	tokens->expand = 0;
	tokens->pos = 0;
	tokens->move = 0;
}

int	count_tokens(t_scan *src)
{
	int		i;
	int		count;
	int		t;

	i = 0;
	t = src->chars[i]->t;
	count = 1;
	while (i < src->len)
	{
		if (src->chars[i]->t != t)
		{
			t = src->chars[i]->t;
			if (!t)
				continue ;
			count++;
		}
		i++;
	}
	return (count);
}

char	*extract_token(t_scan *src)
{
	char	buf[2];
	int		type;
	char	*tok;
	int		pos;
	int		len;

	tok = ft_strdup("");
	pos = src->pos;
	len = src->len;
	type = src->chars[pos]->t;
	while (pos < len && src->chars[pos]->t == type)
	{
		buf[0] = src->chars[pos]->c;
		buf[1] = '\0';
		tok = ft_strjoin_and_free(tok, buf);
		pos++;
	}
	src->pos = pos;
	return (tok);
}

t_token	*create_token(char *input, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	init_token(token);
	token->type = type;
	token->value = ft_strdup(input);
	ft_free(input);
	return (token);
}

t_token	**tokenize(t_scan *src)
{
	t_token	**tokens;
	int		start;
	int		count;
	char	*val;
	int		i;

	count = count_tokens(src);
	tokens = malloc(sizeof(t_token) * count);
	src->pos = 0;
	i = 0;
	while (i < count)
	{
		while (src->chars[src->pos]->t == 0)
			src->pos++;
		start = src->pos;
		val = extract_token(src);
		tokens[i] = create_token(val, src->chars[start]->t);
		if (tokens[i]->value[0] == '\'')
			tokens[i]->quote = 1;
		if (tokens[i]->value[0] == '\"')
			tokens[i]->quote = 2;
		i++;
	}
	tokens[0]->count = count;
	return (tokens);
}
