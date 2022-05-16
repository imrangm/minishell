/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 06:18:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/16 07:24:34 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*set_arg(int i, char *input)
{
	char	*arg;

	if (i > 1)
		arg = rem_words(input);
	else
		arg = ft_strdup("");
	return (arg);
}

char	*set_cmd(char *s1, char *s2)
{
	char	*cmd;

	if (s1[0] == '>' || s1[0] == '<')
		cmd = rem_words(s2);
	else
		cmd = cmd_copy(s1);
	return (cmd);
}

char	*find_cmd(char *input)
{
	int		i;
	char	*cmd;
	char	*args;
	char	**out;

	out = ft_split_rd(input);
	cmd = set_cmd(out[0], out[1]);
	i = 1;
	while (out[i])
	{
		if (word_count(out[i]) > 0)
		{
			args = set_arg(i, out[i]);
			cmd = ft_strjoin(cmd, args);
			printf("%d\n out: %s, cmd: %s\n", i, out[i], cmd);
		}
		i++;
	}
	ft_free_arg(out);
	return (cmd);
}
