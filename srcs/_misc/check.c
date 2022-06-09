/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:34:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/09 18:58:58 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	pc_end(char *line) //? Imran
{
	int	len;

	len = ft_strlen(line);
	if (line[0] == '|' || line[len - 1] == '|') //! Ignore all types of ft_isspace() after it.
		return (error("Error: Last character must not be a pipe symbol.\n"));
	else if (line[len - 1] == '>' || line[len - 1] == '<') //! Ignore all types of ft_isspace() after it.
		return (error("Error: Last character must not be a redirection symbol.\n"));
	return (0);
}

int	pc_pipe(char *line)
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
			free_2d(check);
			return (error("minishell: syntax error\n"));
		}
		i++;
	}
	free_2d(check);
	return (0);
}

int	pc_redir(char *line)
{
	int		i;
	char	**out;

	i = 0;
	out = split_rd(line);
	while (out[i + 1])
	{
		if ((ft_strchr(out[i], '<') || (ft_strchr(out[i], '>')))
			&& check_space(out[i + 1]))
		{
			free_2d(out);
			return (error("minishell: syntax error\n"));
		}
		if (count_redir(out[i]) > 2)
		{
			free_2d(out);
			return (error("minishell: syntax error\n"));
		}
		i++;
	}
	free_2d(out);
	return (0);
}
