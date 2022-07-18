/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/18 07:54:55 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct_rd(t_redirs *rd)
{
	free(rd->infile);
	free(rd->outfile);
	free(rd->heredoc);
	free(rd->append);
	free(rd);
}

void	free_struct_pp(t_pipe **p, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		free(p[i]->fcmd);
		free(p[i]->rd.infile);
		free(p[i]->rd.outfile);
		free(p[i]->rd.heredoc);
		free(p[i]->rd.append);
		free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
}

void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p)
{
	free_3d(arg, p[0]->nchild);
	free_2d_int(pipes, p[0]->nchild);
	free(pids);
	free_struct_pp(p, p[0]->nchild);
}

void	rd_free(int *fd, char **arg, t_redirs *rd)
{
	close_fds(fd);
	free(fd);
	free_2d(arg);
	free_struct_rd(rd);
}
