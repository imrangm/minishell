/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/20 12:12:20 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct_rd(t_redirs *rd)
{
	ft_free(rd->infile);
	ft_free(rd->outfile);
	ft_free(rd->heredoc);
	ft_free(rd->append);
	ft_free(rd);
}

void	free_struct_pp(t_pipe **p, int nchild)
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
	ft_free(p);
}

void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p)
{
	int	i;

	i = 0;
	while (i < p[0]->nchild)
	{
		ft_free_2d(arg[i]);
		i++;
	}
	ft_free(arg);
	i = 0;
	while (i < p[0]->nchild)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	ft_free(pids);
	free_struct_pp(p, p[0]->nchild);
}

void	rd_free(int *fd, char **arg, t_redirs *rd)
{
	close_fds(fd);
	ft_free(fd);
	ft_free_2d(arg);
	free_struct_rd(rd);
}

void	free_data(t_data *data)
{
	ft_free(data->pwd);
	ft_free(data->old_pwd);
	ft_free_2d(data->envp);
}
