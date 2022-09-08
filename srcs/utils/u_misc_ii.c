/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/08 13:21:05 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	line_update(char **line)
{
	char	buf[2];
	char	*temp;

	write(1, "> ", 2);
	temp = strdup("");
	while (1)
	{
		read(STDIN_FILENO, buf, 1);
		buf[1] = '\0';
		temp = ft_strjoin_and_free(temp, buf);
		if (ft_strchr(temp, '\n'))
		{
			*line = ft_strjoin_and_free(*line, temp);
			if (!ft_strchr(temp, '|'))
			{
				ft_free(temp);
				break ;
			}
			ft_free(temp);
			temp = ft_strdup("");
			write(1, "> ", 2);
		}
	}
}

void	update_final(char **final, char **line)
{
	*final = ft_strjoin_and_free(*final, *line);
	ft_free(*line);
	*line = strdup("");
}

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;
	int		bytes;

	set_signalset(0);
	line = ft_strdup("");
	final = ft_strdup("");
	bytes = 0;
	ft_memset(buf, 0, 2);
	write(1, "> ", 2);
	while (1)
	{
		bytes = read(0, buf, 1);
		buf[1] = '\0';
		if (!bytes)
		{
			write(1, "\n", 1);
			ft_putstr_fd("heredoc delimited by end-of-file\n", 2);
			break ;
		}
		line = ft_strjoin_and_free(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (ft_strlen(line) == (ft_strlen(lim) + 1)
				&& (ft_strncmp (line, lim, ft_strlen(lim)) == 0))
				break ;
			if (!bytes)
			{
				write(1, "\n", 1);
				ft_putstr_fd("heredoc delimited by end-of-file\n", 2);
				break ;
			}
			write(1, "> ", 2);
			update_final(&final, &line);
		}
	}
	ft_free(line);
	return (final);
}
