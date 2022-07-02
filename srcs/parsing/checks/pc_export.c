/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:31:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/02 15:15:49 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	equal_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if ((str[i] == '=' && str[i + 1] == '=')
				|| (str[i] == '+' && str[i + 1] != '='))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	invalid_lhs(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i] != '=')
		return (1);
	return (0);
}

static int	is_invalid_export_syntax(char **str, int i)
{
	return (equal_plus(str[i]) || !ft_strcmp(str[i], "=")
		|| !ft_strcmp(str[i], "+=") || !ft_isalpha(str[i][0])
		|| str[i][ft_strlen(str[i]) - 1] == '+' || invalid_lhs(str[i]));
}

int	pc_export(char **args)
{
	int		i;

	i = 1;
	if (ft_strcmp(args[0], "export"))
		return (0);
	while (args[i])
	{
		if (is_invalid_export_syntax(args, i))
		{
			ft_putstr_fd("Error: Invalid export syntax.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
