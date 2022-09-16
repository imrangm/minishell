/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:40:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/16 09:41:05 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_bytes(int bytes)
{
	if (!bytes)
	{
		ft_putstr_fd("\nheredoc delimited by end-of-file\n", 2);
		return (1);
	}
	return (0);
}

int	check_line(char *line, char *lim)
{
	if (ft_strlen(line) == (ft_strlen(lim) + 1)
		&& (ft_strncmp (line, lim, ft_strlen(lim)) == 0))
	{
		return (1);
	}
	return (0);
}

void	update_final(char **final, char **line)
{
	*final = ft_strjoin_and_free(*final, *line);
	ft_free(*line);
	*line = strdup("");
	write(1, "> ", 2);
}

void	init_readline(char **line, char **final, int *bytes)
{
	*line = ft_strdup("");
	*final = ft_strdup("");
	*bytes = 0;
	write(1, "> ", 2);
}

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;
	int		bytes;

	set_signalset(2);
	init_readline(&line, &final, &bytes);
	while (1)
	{
		bytes = read(0, buf, 1);
		buf[1] = '\0';
		if (check_bytes(bytes))
			break ;
		line = ft_strjoin_and_free(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (check_line(line, lim))
				break ;
			if (check_bytes(bytes))
				break ;
			update_final(&final, &line);
		}
	}
	ft_free(line);
	return (final);
}
