/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:46:57 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/09 16:39:42 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*redir_cpy(char *input)
{
	int		i;
	char	*copy;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			break ;
		i++;
	}
	copy = ft_substr(input, i, ft_strlen(input));
	return (copy);
}

char	*cmd_copy(char *input)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char *));
	while (input[i] != '\0')
	{
		if (input[i] == '\"' || input[i] == '\'')
			i++;
		if (input[i] == '<' || input[i] == '>')
			break ;
		copy[j] = input[i];
		j++;
		i++;
	}
	copy[j] = '\0';
	return (copy);
}

void	split_pipe(char *line)
{
	char	**cmd;
	t_pipe	**p;
	int		i;
	int		c;

	i = 0;
	c = count_pipes(line) + 1;
	p = malloc(sizeof(t_pipe *) * c);
	i = 0;
	line = ft_strtrim(line, "\n");
	check_line(line);
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd[i] = ft_strtrim(cmd[i], " ");
		p[i] = malloc(sizeof(t_pipe));
		process(cmd[i], &p[i]->rd);
		p[i]->fcmd = cmd_copy(cmd[i]);
		printf("cmd(%d): %s\n", i, cmd[i]);
		i++;
	}
	pipes(line, p);
}

void	split_rd(char *line)
{
	t_redirs	*rd;
	char		*cmd;
	char		*ln;

	rd = malloc(sizeof(t_redirs));
	line = ft_strtrim(line, "\n");
	line = ft_strtrim(line, " ");
	cmd = cmd_copy(line);
	printf("%s\n", cmd);
	ln = redir_cpy(line);
	printf("%s\n", ln);
	process(ln, rd);
	file(cmd, rd);
}
