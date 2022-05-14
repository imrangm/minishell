/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_rd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:15:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/14 18:16:36 by imustafa         ###   ########.fr       */
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

void	split_multi_cmd_redir(char **input, t_redirs *rd, t_data *data)
{
	char	*args;
	char	*cmd;
	char	*redir;
	char	*file;
	int		i;

	cmd = first_word(input[0]);
	i = 0;
	while (input[i + 2])
	{
		if (word_count(input[i]) > 0)
		{
			args = rem_words(input[i]);
			redir = input[i + 1];
			file = first_word(input[i + 2]);
			cmd = ft_strjoin(cmd, args);
			redir = ft_strjoin(redir, file);
			process(redir, rd);
			create_file(cmd, rd, data);
		}
		i++;
	}
}
