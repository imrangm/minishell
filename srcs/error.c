/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/19 15:58:11 by imustafa         ###   ########.fr       */
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
