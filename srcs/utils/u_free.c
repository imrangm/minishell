/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:23:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/06/09 17:45:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_free(void *ptr)
{
	if (!ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_2d_int(int **arr, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		safe_free(arr[i]);
		i++;
	}
	safe_free(arr);
}

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		safe_free(arr[i]);
		i++;
	}
	safe_free(arr);
}

void	free_3d(char ***arr, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		free_2d(arr[i]);
		i++;
	}
	safe_free(arr);
}
