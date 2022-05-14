/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 06:18:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/14 18:48:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_unquote(char *input)
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

char	*first_word(char *input)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	word = ft_substr(input, 0, i);
	return (word);
}

char	*rem_words(char *input)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	word = ft_substr(input, i, ft_strlen(input));
	return (word);
}

char	*find_cmd(char *input)
{
	int		i;
	int		j;
	char	*cmd;
	char	**out;

	i = 0;
	out = ft_split_rd(input);
	i = 0;
	while (out[i + 1])
	{
		if (word_count(out[i]) > 0)
			break ;
		i++;
	}
	j = 0;
	while (out[i][j + 1])
	{
		if (out[i][j] == ' ' && out[i][j + 1] != ' ')
			break ;
		j++;
	}
	cmd = ft_substr(out[i], ++j, ft_strlen(out[i]));
	return (cmd);
}
