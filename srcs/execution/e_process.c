/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/16 18:27:45 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_rd(t_redirs *rd)
{
	rd->infile = NULL;
	rd->outfile = NULL;
	rd->append = NULL;
	rd->heredoc = NULL;
	rd->lastin = 0;
	rd->lastout = 0;
}

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
		if (rd->heredoc)
		{
			read_line(rd->heredoc);
			ft_free(rd->heredoc);
		}
		rd->heredoc = file;
	}
	if (t == 'i')
	{
		if (rd->infile)
			ft_free(rd->infile);
		rd->infile = file;
	}
	rd->lastin = t;
}

void	assign_outfile(char *file, t_redirs *rd, char t)
{
	if (t == 'a')
	{
		if (rd->append)
		{
			empty_file(rd->append);
			ft_free(rd->append);
		}
		rd->append = file;
	}
	if (t == 'o')
	{
		if (rd->outfile)
		{
			empty_file(rd->outfile);
			ft_free(rd->outfile);
		}
		rd->outfile = file;
	}
	rd->lastout = t;
}

void	process(char *line, t_redirs *rd)
{
	char	**out;
	char	*file;
	int		i;

	i = 0;
	init_rd(rd);
	out = split_rd(line);
	while (out[i + 1] != NULL)
	{
		if (out[i + 1][0] != '<' && out[i + 1][0] != '>')
		{
			file = first_word(out[i + 1]);
			if (ft_strncmp(out[i], "<<", 2) == 0)
				assign_infile(file, rd, 'h');
			else if (ft_strncmp(out[i], "<", 1) == 0)
				assign_infile(file, rd, 'i');
			else if (ft_strncmp(out[i], ">>", 2) == 0)
				assign_outfile(file, rd, 'a');
			else if (ft_strncmp(out[i], ">", 1) == 0)
				assign_outfile(file, rd, 'o');
		}
		i++;
	}
	ft_free_2d(out);
}
