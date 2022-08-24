/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/24 08:03:09 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_redirection(char *left, char *right)
{
	if (ft_strncmp(left, ">>", 2) == 0)
		empty_file(right);
	if (ft_strncmp(left, ">", 1) == 0)
		empty_file(right);
	if (ft_strncmp(left, "<<", 2) == 0)
		read_line(right);
	if (ft_strncmp(left, "<", 1) == 0)
	{
		if (!access(right, F_OK))
		{
			ft_putstr_fd(right, 2);
			ft_putstr_fd(": No such file or directory", 2);
		}
	}
}
