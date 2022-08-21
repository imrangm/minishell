/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/21 13:01:19 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*line_update(void)
{
	char	buf[2];
	char	*line;
	char	*final;

	line = ft_strdup("");
	final = line;
	write(1, "> ", 2);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (!ft_strchr(line, '|'))
				break ;
			write(1, "> ", 2);
			final = ft_strjoin_and_free(final, ft_strtrim(line, "\n"));
			free(line);
			line = strdup("");
		}
	}
	final = ft_strjoin_and_free(final, ft_strtrim(line, "\n"));
	free(line);
	return (final);
}
