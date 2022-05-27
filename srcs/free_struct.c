/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/27 14:35:50 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_struct_rd(t_redirs *rd)
{
	ft_free(rd->infile);
	ft_free(rd->outfile);
	ft_free(rd->heredoc);
	ft_free(rd->append);
	ft_free(rd);
}

void	free_struct_ps(t_pipe **p, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free(p[i]->fcmd);
		ft_free(p[i]->rd.infile);
		ft_free(p[i]->rd.outfile);
		ft_free(p[i]->rd.heredoc);
		ft_free(p[i]->rd.append);
		ft_free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
}

void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p)
{
	ft_free_args(arg, p[0]->nchild);
	ft_free_int(pipes, p[0]->nchild);
	ft_free(pids);
	free_struct_ps(p, p[0]->nchild);
}

void	rd_free(int *fd, char **arg, t_redirs *rd)
{
	close_fds(fd);
	ft_free(fd);
	ft_free_arg(arg);
	free_struct_rd(rd);
}
