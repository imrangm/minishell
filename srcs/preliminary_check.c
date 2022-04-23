/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/23 21:32:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_unclosed_quotes(char *str)
{
	int	i;
	int	sqc;
	int	dqc;

	i = 0;
	sqc = 0;
	dqc = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE)
		{
			dqc = 1;
			i++;
			while (str[i])
			{
				if (str[i] == DQUOTE)
				{
					dqc = 0;
					break ;
				}
				i++;
			}
		}
		if (str[i] == SQUOTE)
		{
			sqc = 1;
			i++;
			while (str[i])
			{
				if (str[i] == SQUOTE)
				{
					sqc = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (dqc || sqc)
	{
		ft_putstr_fd("Error: Unclosed quote detected.\n", 2);
		return (1);
	}
	return (0);
}

/*
* Checks if the user has input a word at the start
* regardless whether or not it's an existing command.
*/
int	is_cmd_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	if (!str[i])
		return (0);
	if (!ft_isalnum(str[i]))
		return (0);
	return (1);
}

/*
* Checks for incorrect redirection syntax,
* forbidden chars, and unclosed quotes.
*/
int	preliminary_check(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	// TODO – Check for: > x echo "hello"
	if (!is_cmd_syntax(str))
		return (0);
	if (contains_unclosed_quotes(str))
		return (0);
	// while (str[i])
	// {
	// 	quote = set_quote(str[i], quote);
	// 	// Checks for double chars
	// 	if (str[i + 1] && !quote)
	// 	{
	// 		if ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '|' && str[i + 1] == '&'))
	// 			return (0);
	// 		if (str[i] == '>' && str[i + 1] == '<')
	// 			return (0);
	// 		if (str[i] == '<' && str[i + 1] == '>')
	// 			return (0);
	// 	}
	// 	if (str[i + 2] && !quote)
	// 	{
	// 		if (str[i] == '>' && str[i + 1] == '>'
	// 			&& (str[i + 2] == '>' || str[i + 2] == '<'))
	// 			return (0);
	// 		if (str[i] == '<' && str[i + 1] == '<'
	// 			&& (str[i + 2] == '>' || str[i + 2] == '<'))
	// 			return (0);
	// 	}
	// 	i++;
	// }
	return (1);
}
