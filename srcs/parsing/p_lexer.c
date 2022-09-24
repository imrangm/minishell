/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:07:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:35 by nmadi            ###   ########.fr       */
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

t_token	*create_token(char *input, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	init_token(token);
	token->type = type;
	token->value = input;
	token->next = NULL;
	return (token);
}

t_toklist	*create_toklist(t_token *head)
{
	t_toklist	*tokens;

	tokens = malloc(sizeof(t_toklist));
	init_toklist(tokens);
	tokens->first = head;
	tokens->count = count_tokens(head);
	return (tokens);
}

t_token	*extract_token(t_charlist *src)
{
	int		type;
	char	*tok;
	int		pos;
	int		q;

	tok = NULL;
	tok = ft_strdup("");
	pos = src->pos;
	type = src->chars[pos]->t;
	q = 0;
	while (pos < src->len && src->chars[pos]->t == type)
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
	return (create_token(tok, type));
}

t_toklist	*tokenize(t_charlist *src)
{
	t_token		*token;
	t_token		*head;
	t_token		*last;
	int			sp;

	src->pos = 0;
	head = NULL;
	while (src->pos < src->len)
	{
		if (src->chars[src->pos]->t == 0)
			sp = 1;
		else
			sp = 0;
		while (src->chars[src->pos]->t == 0)
			src->pos++;
		token = extract_token(src);
		if (sp)
			token->space = sp;
		if (!head)
			head = token;
		else
			last->next = token;
		last = token;
	}
	return (create_toklist(head));
}
