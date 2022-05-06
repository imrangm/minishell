/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:43:35 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/06 18:57:40 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_without_last_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i - 1 == ft_strlen_int(str))
		{
			if (str[i] != '\n')
				write(1, &str[i], 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}

int	b_echo(char *str, char *flag, char **args)
{
	int	i;

	i = 1;
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
	{
		if (!ft_strncmp(flag, "-n", ft_strlen(str)))
		{
			i = 2;
			while (args[i])
			{
				print_without_last_nl(args[i]);
				i++;
			}
		}
		else
		{
			while (args[i])
			{
				if (!args[i + 1])
					printf("%s\n", args[i]);
				else
					printf("%s", args[i]);
				i++;
			}
		}
	}
	return (0);
}