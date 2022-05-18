/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:34:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/18 22:08:29 by imustafa         ###   ########.fr       */
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

int	p_check_end(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[0] == '|' || line[len - 1] == '|'
		|| line[len - 1] == '>' || line[len - 1] == '<')
		return (error("minishell: syntax error\n"));
	return (0);
}

int	p_check_pipe(char *line)
{
	int		i;
	char	**check;

	i = 0;
	check = ft_split(line, ' ');
	while (check[i + 1])
	{
		if ((ft_strncmp(check[i], "|", 1)) == 0
			&& (ft_strncmp(check[i + 1], "|", 1) == 0))
		{
			ft_free_arg(check);
			return (error("minishell: syntax error\n"));
		}
		i++;
	}
	ft_free_arg(check);
	return (0);
}

int	p_check_redir(char *line)
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
		{
			ft_free_arg(out);
			return (error("minishell: syntax error\n"));
		}
		if (count_redir(out[i]) > 2)
		{
			ft_free_arg(out);
			return (error("minishell: syntax error\n"));
		}
		i++;
	}
	ft_free_arg(out);
	return (0);
}
