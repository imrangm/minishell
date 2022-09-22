/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:20 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/22 17:32:38 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pc_chars(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (!q && (str[i] == '\\' || str[i] == ';' || str[i] == '&'
				|| str[i] == '!' || str[i] == '`' || str[i] == '('
				|| str[i] == ')' || str[i] == '#' || str[i] == '*'))
		{
			ft_putstr_fd("Error: ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putstr_fd(" is a forbidden character.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	pc_quotes(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		i++;
	}
	if (!q)
		return (0);
	ft_putstr_fd("Error: Unclosed quote detected.\n", 2);
	return (1);
}

static int	pc_end(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (ft_isspace(line[len]))
		len--;
	if (line[0] == '|')
	{
		ft_putstr_fd("Error: First character must not be a pipe symbol.\n", 2);
		return (1);
	}
	else if (line[len] == '>' || line[len] == '<')
	{
		ft_putstr_fd(
			"Error: Last character must not be a redirection symbol.\n", 2);
		return (1);
	}
	return (0);
}

// static int	pc_pipe(char *line)
// {
// 	int	i;
// 	int	q;
// 	int	p;

// 	i = 0;
// 	q = 0;
// 	p = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) && !q)
// 			q = line[i];
// 		else if (q && line[i] == q)
// 			q = 0;
// 		else if (!q && line[i] == '|')
// 			p = 1;
// 		else if (p)
// 		{
// 			if (line[i])
// 			{

// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	pc_valid(char *line, t_data *data)
{
	if (ft_arespaces(line))
		return (0);
	if (pc_quotes(line) || pc_chars(line) || pc_redirs(line)
		|| pc_end(line))
	{
		data->last_exit_status = 1;
		return (0);
	}
	return (1);
}
