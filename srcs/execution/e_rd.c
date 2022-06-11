/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:46:57 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/09 18:30:14 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*cmd_copy(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*copy;

	i = 0;
	j = 0;
	size = 0;
	while (input[i] && input[i] != '<' && input[i] != '>')
	{
		size++;
		i++;
	}
	copy = (char *) malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '<' && input[i] != '>')
		copy[j++] = input[i++];
	copy[j] = '\0';
	return (copy);
}

void	execute_rd(char *line, t_data *data)
{
	t_redirs	*rd;
	char		*cmd;

	rd = malloc(sizeof(t_redirs));
	if (!rd)
		return ;
	cmd = find_cmd(line);
	process(line, rd);
	create_file(cmd, rd, data);
}

void	handle_pp(char *line, t_data *data)
{
	char	**cmd;
	t_pipe	**p;
	int		i;
	int		c;

	i = 0;
	c = count_pipes(line) + 1;
	p = malloc(sizeof(t_pipe *) * c);
	if (!p)
		return ;
	cmd = split_pp(line, '|');
	while (cmd[i])
	{
		p[i] = malloc(sizeof(t_pipe));
		if (!p[i])
			return ;
		process(cmd[i], &p[i]->rd);
		p[i]->fcmd = find_cmd(cmd[i]);
		i++;
	}
	p[0]->data = data;
	p[0]->nchild = c;
	pipes(p);
	free_2d(cmd);
}
