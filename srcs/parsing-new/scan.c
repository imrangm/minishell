/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:50:55 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/29 05:59:37 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_type(char c, t_type *chars)
{
	chars->c = c;
	if (chars->t)
		return (chars->t);
	else if (ft_isspace(c))
		chars->t = SPACES;
	else if (ft_isalnum(c) || c == '-'
		|| c == '$' || c == '?' || c == '=')
		chars->t = WORD;
	else if (c == '|')
		chars->t = PIPE;
	else if (c == '>' || c == '<')
		chars->t = REDIR;
	else if (c == '\'')
		chars->t = SQUOTE;
	else if (c == '\"')
		chars->t = DQUOTE;
	else
		chars->t = UNKNWN;
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

void	assign_type(char *input, t_scan *scan)
{
	int	i;
	int	q;
	int	type;

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
}

t_scan	*scan_input(char *input)
{
	int		i;
	int		len;
	t_scan	*scan;

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
	assign_type(input, scan);
	return (scan);
}
