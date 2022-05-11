/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 19:04:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Print error from the system and exit program
*/
void	err_print(int error, t_data *data)
{
	perror("Error");
	data->last_exit_status = error;
	exit(data->last_exit_status);
}

void	err_free_parent(int **pipes, int *pids)
{
	ft_free(pipes);
	free(pids);
	// exit(code);
}

void	err_free_pipex(int **pipes, char ***args)
{
	ft_free(pipes);
	ft_free_args(args);
	perror("Error");
	// exit (error);
}
