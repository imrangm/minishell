/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:43:35 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/06 15:42:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_putchar(int c)
{
	write (1, &c, 1);
}

static void	print_with_stripped_quotes(char *str, int space, int nl)
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

static int	is_n_flag(char *str)
{
	int	i;

	i = 1;
	if (!ft_strcmp(str, "-n"))
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
	if (ft_strcmp(data->line, "echo") == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	normal_mode = !is_n_flag(args[1]);
	(void) data;
	while (args[i] && is_n_flag(args[i]))
		i++;
	while (args[i])
	{
		if (!args[i + 1] && !normal_mode)
			print_with_stripped_quotes(args[i], 0, 0);
		else if (!args[i + 1] && normal_mode)
			print_with_stripped_quotes(args[i], 0, 1);
		else
			print_with_stripped_quotes(args[i], 1, 0);
		i++;
	}
	return (0);
}
