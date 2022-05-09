/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:34:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/09 17:13:47 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe(char *line)
{
	int		i;
	char	**check;
	int		len;

	i = 0;
	len = ft_strlen(line);
	if (line[len - 1] == '|')
	{
		ft_putstr_fd("syntax error 1\n", 2);
		return (1);
	}
	check = ft_split(line, ' ');
	while (check[i + 1])
	{
		if ((ft_strncmp(check[i], "|", 1)) == 0
			&& (ft_strncmp(check[i + 1], "|", 1) == 0))
		{
			ft_putstr_fd("syntax error 2\n", 2);
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_redir(char *line)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	line = ft_strtrim(line, " ");
	len = ft_strlen(line);
	if (line[len - 1] == '>' || line[len - 1] == '<')
	{
		ft_putstr_fd("syntax error 1\n", 2);
		return (1);
	}
	return (0);
}
