/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:43:26 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/17 08:01:37 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(int fdi, int fdo)
{
	if (fdi != 0)
		close(fdi);
	if (fdo != 1)
		close(fdo);
}

int	word_count(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] == ' ' && input[i + 1] != ' ')
			c++;
		i++;
	}
	return (c);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

int	check_space(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			c++;
		i++;
	}
	if (i == c)
		return (1);
	return (0);
}

char	*line_unquote(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*copy;

	i = 0;
	j = 0;
	size = 0;
	while (input[i++])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i++;
		size++;
	}
	copy = (char *) malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (input[i++])
	{
		if (input[i] != '\'' || input[i] != '\"')
			copy[j++] = input[i++];
	}
	copy[j] = '\0';
	return (copy);
}
