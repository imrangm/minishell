/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/03 14:30:06 by imustafa         ###   ########.fr       */
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

char	*read_line(char *lim)
{
	char	buf[2];
	char	*line;
	char	*final;

	line = ft_strdup("");
	final = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		line = ft_strjoin_and_free(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (!ft_strncmp (line, lim, ft_strlen(lim)))
				break ;
			final = ft_strjoin_and_free(final, line);
			ft_free(line);
			line = strdup("");
			write(1, "> ", 2);
		}
	}
	ft_free(line);
	return (final);
}
