/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:43:35 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/07 17:15:46 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_echo(char **args)
{
	int	i;
	int	normal_mode;

	i = 1;
	normal_mode = ft_strncmp(args[1], "-n", ft_strlen(args[1]));
	if (!normal_mode)
		i = 2;
	while (args[i])
	{
		if (!args[i + 1] && !normal_mode)
			printf("%s", args[i]);
		else if (!args[i + 1] && normal_mode)
			printf("%s\n", args[i]);
		else
			printf("%s ", args[i]);
		i++;
	}
	return (0);
}
