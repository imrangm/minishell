/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:23:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/26 18:00:59 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(void *ptr)
{
	if (!ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

//? changed
void	ft_free_int(int **arr, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free (arr);
	arr = NULL;
}

void	ft_free_arg(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

void	ft_free_args(char ***arr, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		ft_free_arg(arr[i]);
		i++;
	}
	free (arr);
	arr = NULL;
}
