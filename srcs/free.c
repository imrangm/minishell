/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:23:13 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/19 14:52:34 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** freeing memory allocated through malloc
*/
void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_int(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
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
			j++;
		}
		arr[i] = NULL;
		i++;
	}
	free (arr);
	arr = NULL;
}

void	free_struct(t_redirs *rd)
{
	ft_free(rd->infile);
	ft_free(rd->outfile);
	ft_free(rd->heredoc);
	ft_free(rd->append);
	ft_free(rd);
}
