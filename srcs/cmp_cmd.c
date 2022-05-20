/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:23:41 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/20 16:27:25 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmp_cmd(char *cmd, char *builtin)
{
	int	i;

	i = 0;
	while (cmd[i] && builtin[i])
	{
		if (cmd[i] != builtin[i])
			return (1);
		i++;
	}
	if (cmd[i] || builtin[i])
		return (1);
	return (0);
}
