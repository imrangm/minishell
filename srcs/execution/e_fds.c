/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:08:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/05 13:49:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_in(t_redirs *rd)
{
	char	*text;
	int		fd;

	fd = STDIN_FILENO;
	if (rd->heredoc)
	{
		fd = open("tmp", rd->lastin, 0644);
		text = read_line(rd->heredoc);
		write(fd, text, strlen(text));
		close(fd);
		ft_free(text);
	}
	else if (rd->infile)
		fd = open(rd->infile, rd->lastin);
	return (fd);
}

int	fd_out(t_redirs *rd)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (rd->outfile)
		fd = open(rd->outfile, rd->lastout, 0644);
	else if (rd->append)
		fd = open(rd->append, rd->lastout, 0644);
	return (fd);
}

void	close_fds(int *fd)
{
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}
