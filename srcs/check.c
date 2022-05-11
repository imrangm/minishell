/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:34:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/10 21:48:31 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

int	count_redir(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			c++;
		i++;
	}
	return (c);
}

int	check_end(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[0] == '|' || line[len - 1] == '|'
		|| line[len - 1] == '>' || line[len - 1] == '<')
		return (error("minishell: syntax error\n"));
	return (0);
}

int	check_pipe(char *line)
{
	int		i;
	char	**check;

	i = 0;
	check = ft_split(line, ' ');
	while (check[i + 1])
	{
		if ((ft_strncmp(check[i], "|", 1)) == 0
			&& (ft_strncmp(check[i + 1], "|", 1) == 0))
			return (error("minishell: syntax error\n"));
		i++;
	}
	return (0);
}

int	check_redir(char *line)
{
	int		i;
	char	**out;

	i = 0;
	out = ft_split_rd(line);
	while (out[i + 1])
	{
		out[i + 1] = ft_strtrim(out[i + 1], " ");
		if ((ft_strchr(out[i], '<') || (ft_strchr(out[i], '>')))
			&& check_space(out[i + 1]))
			return (error("minishell: syntax error\n"));
		if (count_redir(out[i]) > 2)
			return (error("minishell: syntax error\n"));
		i++;
	}
	return (0);
}
