/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:43:35 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 22:17:43 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar(int c)
{
	write (1, &c, 1);
}

void	print_with_stripped_quotes(char *str, int space, int nl)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !d)
			d = str[i];
		else if (str[i] == d)
			d = 0;
		else
			ft_putchar(str[i]);
		i++;
	}
	if (nl)
		ft_putchar('\n');
	if (space)
		ft_putchar(32);
}

int	is_n_flag(char *str)
{
	int	i;

	i = 1;
	if (!ft_strncmp(str, "-n", ft_strlen(str)))
		return (1);
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	b_echo(char **args, t_data *data)
{
	int	i;
	int	normal_mode;

	i = 1;
	normal_mode = !is_n_flag(args[1]);
	while (args[i] && is_n_flag(args[i]))
		i++;
	while (args[i])
	{
		if (args[i + 1] && !ft_strncmp(args[i], "$?", ft_strlen(args[i])))
			printf("%d ", data->last_exit_status);
		else if (!args[i + 1] && !ft_strncmp(args[i], "$?", ft_strlen(args[i])))
			printf("%d\n", data->last_exit_status);
		else if (!args[i + 1] && !normal_mode)
			print_with_stripped_quotes(args[i], 0, 0);
		else if (!args[i + 1] && normal_mode)
			print_with_stripped_quotes(args[i], 0, 1);
		else
			print_with_stripped_quotes(args[i], 1, 0);
		i++;
	}
	return (0);
}
