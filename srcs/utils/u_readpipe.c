/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:13:15 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:14:18 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_only(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '|')
			return (0);
		i++;
	}
	return (1);
}

char	*end_of_line(char *line, char *temp)
{
	ft_free(temp);
	ft_putendl_fd("Error: unexpected end of file", 2);
	return (trim_line(line));
}

void	add_line(char **line, char **temp)
{
	*line = ft_strjoin_and_free(*line, " ");
	*line = ft_strjoin_and_free(*line, *temp);
}

int	check_input(char **temp)
{
	if (end_pipe(*temp) && !pipe_only(*temp))
	{
		ft_free(*temp);
		*temp = ft_strdup("");
		write(1, "> ", 2);
	}
	else
	{
		ft_free(*temp);
		return (1);
	}
	return (0);
}

char	*read_pipe(char *line)
{
	char	buf[2];
	char	*temp;
	int		rv;

	set_signalset(2);
	temp = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		rv = read(STDIN_FILENO, buf, 1);
		if (!rv)
			return (end_of_line(line, temp));
		buf[rv] = '\0';
		if (buf[0] != '\n')
			temp = ft_strjoin_and_free(temp, buf);
		else
		{
			add_line(&line, &temp);
			if (check_input(&temp))
				break ;
		}
	}
	return (trim_line(line));
}
