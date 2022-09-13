/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:07:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 19:06:53 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*update_token(char *tok, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tok = ft_strjoin_and_free(tok, buf);
	return (tok);
}

char	*extract_token(t_scan *src)
{
	int		type;
	char	*tok;
	int		pos;
	int		len;
	int		q;

	tok = NULL;
	tok = ft_strdup("");
	pos = src->pos;
	len = src->len;
	type = src->chars[pos]->t;
	q = 0;
	while (pos < len && src->chars[pos]->t == type)
	{
		if (ft_isquote(src->chars[pos]->c) && !q)
			q = src->chars[pos]->c;
		else if (q == src->chars[pos]->c)
		{
			tok = update_token(tok, src->chars[pos]->c);
			pos++;
			break ;
		}
		tok = update_token(tok, src->chars[pos]->c);
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
	token->next = NULL;
	return (token);
}

t_token	*tokenize(t_scan *src)
{
	t_token	*token;
	t_token	*top;
	t_token	*last;
	int		start;
	// int		count;
	char	*val;
	int		sp;
	// int		i;

	// count = count_tokens(src);
	// tokens = malloc(sizeof(t_token) * count);
	src->pos = 0;
	top = NULL;
	// i = 0;
	while (src->pos < src->len)
	{
		if (src->chars[src->pos]->t == 0)
			sp = 1;
		else
			sp = 0;
		while (src->chars[src->pos]->t == 0)
			src->pos++;
		start = src->pos;
		val = extract_token(src);
		token = create_token(val, src->chars[start]->t);
		if (sp)
			token->space = sp;
		if (!top)
			top = token;
		else
			last->next = token;
		last = token;
		// i++;
	}
	// token[0]->count = count;
	return (top);
}
