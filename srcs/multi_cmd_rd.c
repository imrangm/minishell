/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_rd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:15:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/15 20:19:03 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	multi_cmd_redir(char *input)
{
	int		i;
	int		wc;
	char	**out;

	i = 0;
	wc = 0;
	out = ft_split_rd(input);
	while (out[i])
	{
		if (word_count(out[i]) > 0)
			wc++;
		i++;
	}
	if (wc > 1)
		return (1);
	return (0);
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
		cmd = find_cmd(s2);
	else
		cmd = cmd_copy(s1);
	return (cmd);
}

void	split_multi_cmd_redir(char **input, t_redirs *rd, t_data *data)
{
	char	*args;
	char	*cmd;
	char	*redir;
	char	*file;
	int		i;

	cmd = set_cmd(input[0], input[1]);
	i = 0;
	while (input[i + 2])
	{
		if (word_count(input[i]) > 0)
		{
			args = set_arg(i, input[i]);
			redir = input[i + 1];
			file = first_word(input[i + 2]);
			empty_file(file);
			cmd = ft_strjoin(cmd, args);
			redir = ft_strjoin(redir, file);
		}
		i++;
	}
	process(redir, rd);
	create_file(cmd, rd, data);
}
