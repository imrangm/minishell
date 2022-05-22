/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/22 11:53:35 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	err_print(int error, t_data *data)
{
	perror("Error");
	data->last_exit_status = error;
}

void	err_free_parent(int **pipes, int *pids)
{
	ft_free_int(pipes);
	ft_free(pids);
	perror("Error");
}

void	err_free_process(int **pipes, char ***args)
{
	ft_free_int(pipes);
	ft_free_args(args);
	perror("Error");
}
