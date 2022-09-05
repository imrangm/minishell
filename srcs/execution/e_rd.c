/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_rd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:46:57 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/05 06:39:58 by imustafa         ###   ########.fr       */
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

int	here_pipe(t_pipe *p)
{
	int		fdi;
	char	*text;

	fdi = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdi == -1)
		return (-1);
	text = read_line(p->rd.heredoc);
	write(fdi, text, strlen(text));
	close(fdi);
	if (p->rd.lastin == 'h')
	{
		fdi = open("tmp", O_RDONLY, 0);
		if (fdi == -1)
			return (-1);
		dup2(fdi, STDIN_FILENO);
	}
	else
	{
		fdi = open(p->rd.infile, O_RDONLY, 0);
		dup2(fdi, STDIN_FILENO);
	}
	close(fdi);
	return (1);
}

int	redir_in(t_pipe **p, int i)
{
	int	fd;
	int	ret;

	fd = 0;
	if (p[i]->rd.heredoc)
	{
		ret = here_pipe(p[i]);
		return (ret);
	}
	else if (p[i]->rd.infile)
	{
		fd = open(p[i]->rd.infile, O_RDONLY);
		if (fd == -1)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}

int	redir_out(t_pipe **p, int i)
{
	int	fd;

	if (p[i]->rd.outfile)
	{
		fd = open(p[i]->rd.outfile, p[i]->rd.lastout, 0644);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	else if (p[i]->rd.append)
	{
		fd = open(p[i]->rd.append, p[i]->rd.lastout, 0644);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}
