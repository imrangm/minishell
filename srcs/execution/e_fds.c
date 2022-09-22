/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_fds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:08:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/22 14:38:21 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_in(t_redirs *rd)
{
	char	*text;
	int		fd;
	int		p[2];

	fd = STDIN_FILENO;
	if (rd->heredoc)
	{
		if (pipe(p) == -1)
			return (-1);
		text = read_line(rd->heredoc);
		ft_putstr_fd(text, p[1]);
		fd = p[0];
		ft_free(text);
		close(p[1]);
	}
	else if (rd->infile)
	{
		fd = open(rd->infile, rd->lastin);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

int	fd_out(t_redirs *rd)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (rd->outfile)
	{
		fd = open(rd->outfile, rd->lastout, 0644);
		if (fd == -1)
			return (-1);
	}
	else if (rd->append)
	{
		fd = open(rd->append, rd->lastout, 0644);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

void	close_fds(int *fd)
{
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}
