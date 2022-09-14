/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_iii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:06:29 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/14 06:53:46 by imustafa         ###   ########.fr       */
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

int	check_bytes(int bytes)
{
	if (!bytes)
	{
		ft_putstr_fd("\nheredoc delimited by end-of-file\n", 2);
		return (1);
	}
	return (0);
}
