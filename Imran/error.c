/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:21:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/19 11:26:30 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

/*
** Print error from the system and exit program
*/
void	err_print(int error)
{
	perror("Error");
	exit (error);
}

void	err_free_parent(int **pipes, int *pids, int code)
{
	ft_free(pipes);
	free(pids);
	exit(code);
}

void	err_free_pipex(int **pipes, char ***args, int error)
{
	ft_free(pipes);
	ft_free_args(args);
	perror("Error");
	exit (error);
}

