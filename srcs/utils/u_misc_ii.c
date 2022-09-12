/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/12 12:37:32 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_final(char **final, char **line)
{
	*final = ft_strjoin_and_free(*final, *line);
	ft_free(*line);
	*line = strdup("");
}

void	ft_readline(char *lim)
{
	char	*text;

	text = read_line(lim);
	free(text);
}

static void	init_rl(char *line, char *final, char *buf, int *bytes)
{
	set_signalset(2);
	line = ft_strdup("");
	final = ft_strdup("");
	*bytes = 0;
	ft_memset(buf, 0, 2);
	write(1, "> ", 2);
}

static void	term_rl(char *final, char *line)
{
	write(1, "> ", 2);
	final = ft_strjoin_and_free(final, line);
	ft_free(line);
	line = strdup("");
}

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;
	int		bytes;

	init_rl(line, final, buf, &bytes);
	while (1)
	{
		bytes = read(0, buf, 1);
		buf[1] = '\0';
		if (check_bytes(bytes))
			break ;
		line = ft_strjoin_and_free(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (ft_strlen(line) == (ft_strlen(lim) + 1)
				&& (ft_strncmp (line, lim, ft_strlen(lim)) == 0))
				break ;
			if (check_bytes(bytes))
				break ;
			term_rl(final, line);
		}
	}
	ft_free(line);
	return (final);
}
