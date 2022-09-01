/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/31 10:54:55 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	free_struct_rd(t_redirs *rd)
// {
	// ft_free(rd->infile);
	// ft_free(rd->outfile);
	// ft_free(rd->heredoc);
	// ft_free(rd->append);
// 	ft_free(rd);
// }

void	free_struct_pp(t_pipe **p, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		// ft_free(p[i]->fcmd);
		// ft_free(p[i]->rd.infile);
		// ft_free(p[i]->rd.outfile);
		// ft_free(p[i]->rd.heredoc);
		// ft_free(p[i]->rd.append);
		ft_free(p[i]);
		i++;
	}
	ft_free(p);
}

void	ps_free(int **pipes, int *pids, t_pipe **p)
{
	int	i;

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
	(void) rd;
	// close_fds(fd);
	ft_free(fd);
	ft_free_2d(arg);
	// free_struct_rd(rd);
}

void	free_data(t_data *data)
{
	ft_free(data->pwd);
	ft_free_2d(data->envp);
}
