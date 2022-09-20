/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:43:26 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 11:39:16 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_strjoin_and_free(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	ft_free(s1);
	return (str);
}

int	count_pipes(char *line)
{
	int	i;
	int	p;
	int	q;

	i = 0;
	p = 0;
	q = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]) && !q)
			q = line[i];
		else if (line[i] == q)
			q = 0;
		else if (line[i] == '|')
			p++;
		i++;
	}
	return (p);
}

int	end_pipe(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(line) - 1;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[j]))
		j--;
	if (line[j + i] == '|')
		return (1);
	return (0);
}

char	*trim_line(char *line)
{
	int		i;
	int		len;
	char	*trimmed;

	i = 0;
	trimmed = NULL;
	len = ft_strlen(line);
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[len - 1]))
		len--;
	if (line[i])
		trimmed = ft_substr(line, i, len - i);
	ft_free(line);
	return (trimmed);
}
