/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 06:18:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/13 06:22:10 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_count(char *input)
{
	int	i;
	int	c;

	input = ft_strtrim(input, " ");
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
	int		c;
	char	*word;

	c = 0;
	i = 0;
	while (input[i] != ' ')
	{
		i++;
		c++;
	}
	word = malloc (sizeof (char) * (c + 1));
	i = 0;
	while (input[i] != ' ')
	{
		word[i] = input[i];
		i++;
	}
	word[i] = '\0';
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
	while (out[i])
	{
		printf("out(%d): %s\n", i, out[i]);
		i++;
	}
	i = 0;
	while (out[i])
	{
		j = 0;
		if (out[i][0] == '<' || out[i][0] == '>')
		{
			while (out[i + 1][j + 1])
			{
				if (out[i + 1][j] == ' ' && out[i + 1][j + 1] != ' ')
				{
					break ;
				}
				j++;
			}
		}
		if (j)
			break ;
		i++;
	}
	cmd = ft_substr(out[i + 1], j, ft_strlen(out[i + 1]));
	printf("cmd: %s\n", cmd);
	return (cmd);
}
