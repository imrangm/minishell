/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:23:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/20 19:49:34 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** free memory allocated through ft_split
*/
void	ft_free(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free (arr);
	arr = NULL;
}

void	ft_free_arg(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free (arr);
	arr = NULL;
}

void	ft_free_args(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		while (arr[i][j])
		{
			free(arr[i][j]);
			arr[i][j] = NULL;
		}
		arr[i] = NULL;
	}
	free (arr);
	arr = NULL;
}
