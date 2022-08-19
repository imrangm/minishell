/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:50:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/18 18:55:11 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	peek_type(char c)
{
	if (ft_isalnum(c) || c == '-')
		return (WORD);
	if (c == '|')
		return (PIPE);
	if (c == '>' || c == '<')
		return (REDIR);
	if (c == '\'')
		return (SQUOTE);
	if (c == '\"')
		return (DQUOTE);
	return (0);
}

//returning type so that when quotes is discovered
//then everything until next quote should be
//a single string
int	set_type(char c, t_type *chars)
{
	chars->c = c;
	if (chars->t)
		return (chars->t);
	if (ft_isalnum(c) || c == '-' || c == '$')
		chars->t = WORD;
	if (c == '|')
		chars->t = PIPE;
	if (c == '>' || c == '<')
		chars->t = REDIR;
	if (c == '\'')
		chars->t = SQUOTE;
	if (c == '\"')
		chars->t = DQUOTE;
	//add else with unexpected token error
	return (chars->t);
}

void	init_chars(t_type **chars, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		chars[i]->c = 0;
		chars[i]->t = 0;
		i++;
	}
}

t_scan	*scan_input(char *input)
{
	int		i;
	int		len;
	t_scan	*scan;
	int		type;
	int		q;

	len = ft_strlen(input);
	scan = malloc(sizeof (t_scan));
	scan->chars = malloc(sizeof(t_type *) * len);
	scan->len = len;
	i = 0;
	while (i < len)
	{
		scan->chars[i] = malloc(sizeof(t_type));
		i++;
	}
	init_chars(scan->chars, len);
	i = 0;
	q = 0;
	while (input[i])
	{
		type = set_type(input[i], scan->chars[i]);
		if (type == SQUOTE || type == DQUOTE)
		{
			if (!q)
				q = type;
			else if (q == type)
				q = 0;
		}
		if (q)
		{
			scan->chars[i]->t = q;
			type = set_type(input[i], scan->chars[i]);
		}
		i++;
	}
	return (scan);
}

void	test_scan(char	*input)
{
	int		len;
	t_scan	*scan;
	int		i;
	
	len = ft_strlen(input);
	printf("------------------------\n");
	printf("%d Chars\n", len);
	scan = scan_input(input);
	i = 0;
	while (i < len)
	{
		printf("%d- C: %c T: %d\n", i, scan->chars[i]->c, scan->chars[i]->t);
		i++;
	}
}
