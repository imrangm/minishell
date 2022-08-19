/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:07:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/18 18:55:03 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
convert into individual characters into tokens(smallest unit 
to be processed); this is also called lexical analysis
*/
void	init_token(t_token *tokens)
{
	tokens->type = 0;
	tokens->value = NULL;
	tokens->iter = 0;
	tokens->cur = 0;
	tokens->count = 0;
	// tokens->next = NULL;
	// tokens->prev = NULL;
}

//count individual strings to be separated into tokens
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

//it is to extract the string that needs to be stored 
//in separate tokens; it will allocate memory for it too
char	*extract_token(t_scan *src)
{
	char	buf[2];
	int		type;
	char	*tok;
	int		pos;
	int		len;

	tok = strdup("");
	pos = src->pos;
	len = src->len;
	type = src->chars[pos]->t;
	while (pos < len && src->chars[pos]->t == type)
	{
		buf[0] = src->chars[pos]->c;
		buf[1] = '\0';
		tok = ft_strjoin(tok, buf);
		pos++;
	}
	src->pos = pos;
	// printf("pos: %d\n", pos);
	return (tok);
}

//takes a string and converts it into a token
t_token	*create_token(char *input, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = malloc(sizeof(char) * (ft_strlen(input) + 1));
	init_token(token);
	token->type = type;
	token->value = input;
	return (token);
}

//think of how to save position of the scanner
//scan text; count individual strings and create a 
//linked list of tokens for each
t_token	**tokenize(t_scan *src)
{
	t_token	**tokens;
	int		start;
	int		count;
	char	*val;
	int		i;

	count = count_tokens(src);
	tokens = malloc(sizeof(t_token) * (count + 1));
	src->pos = 0;
	i = 0;
	while (i < count)
	{
		while (src->chars[src->pos]->t == 0)
			src->pos++;
		start = src->pos;
		val = extract_token(src);
		tokens[i] = create_token(val, src->chars[start]->t);
		i++;
	}
	tokens[0]->count = count;
	tokens[i] = NULL;
	return (tokens);
}

void	test_tokenize(t_scan *source)
{
	t_token	**tokens;
	int		i;
	int		count;

	i = 0;
	count = count_tokens(source);
	printf("------------------------\n");
	printf("%d Tokens\n", count);
	tokens = tokenize(source);
	while (i < count)
	{
		printf("%d: \" %s \"\n", tokens[i]->type, tokens[i]->value);
		i++;
	}
}