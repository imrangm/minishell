/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/13 06:08:05 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	create_file(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC, 0644);
	close(fd);
}

void	assign_file(char *file, t_redirs *rd, char t)
{
	if (t == 'h')
	{
		rd->heredoc = file;
		rd->lastin = 'h';
	}
	if (t == 'i')
	{
		rd->infile = file;
		rd->lastin = 'i';
	}
	if (t == 'a')
	{
		if (rd->append)
			create_file(rd->append);
		rd->append = file;
		rd->lastout = 'a';
	}
	if (t == 'o')
	{
		if (rd->outfile)
			create_file(rd->outfile);
		rd->outfile = file;
		rd->lastout = 'o';
	}
}

void	process(char *line, t_redirs *rd)
{
	char	**out;
	char	*file;
	int		i;

	i = 0;
	rd->lastin = 0;
	rd->lastout = 0;
	out = ft_split_rd(line);
	while (out[i + 1] != NULL)
	{
		file = ft_strtrim(out[i + 1], " ");
		if (word_count(file) > 1)
			file = first_word(file);
		if (ft_strncmp(out[i], "<<", 2) == 0)
		{
			if (rd->heredoc)
				read_line(rd->heredoc);
			assign_file(file, rd, 'h');
		}
		else if (ft_strncmp(out[i], "<", 1) == 0)
			assign_file(file, rd, 'i');
		else if (ft_strncmp(out[i], ">>", 2) == 0)
			assign_file(file, rd, 'a');
		else if (ft_strncmp(out[i], ">", 1) == 0)
			assign_file(file, rd, 'o');
		i++;
	}
}
