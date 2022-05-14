/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/14 18:45:25 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_file(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC, 0644);
	close(fd);
}

void	assign_infile(char *file, t_redirs *rd, char t)
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
}

void	assign_outfile(char *file, t_redirs *rd, char t)
{
	if (t == 'a')
	{
		if (rd->append)
			empty_file(rd->append);
		else
			rd->append = file;
		rd->lastout = 'a';
	}
	if (t == 'o')
	{
		if (rd->outfile)
			empty_file(rd->outfile);
		else
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
	reset_rd(rd);
	out = ft_split_rd(line);
	while (out[i + 1] != NULL)
	{
		file = first_word(out[i + 1]);
		if (ft_strncmp(out[i], "<<", 2) == 0)
		{
			if (rd->heredoc)
				read_line(rd->heredoc);
			assign_infile(file, rd, 'h');
		}
		else if (ft_strncmp(out[i], "<", 1) == 0)
			assign_infile(file, rd, 'i');
		else if (ft_strncmp(out[i], ">>", 2) == 0)
			assign_outfile(file, rd, 'a');
		else if (ft_strncmp(out[i], ">", 1) == 0)
			assign_outfile(file, rd, 'o');
		i++;
	}
}
