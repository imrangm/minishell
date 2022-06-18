/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:31:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/18 18:22:14 by imustafa         ###   ########.fr       */
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

int	export_mode(char **str_split)
{
	if (ft_strcmp(str_split[0], "export"))
	{
		free_2d(str_split);
		return (0);
	}
	return (1);
}

static int	invalid_lhs(char *str)
{
	int	i;
	// int	f; //variable unused

	i = 0;
	// f = 0;
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

int	pc_export(char *str)
{
	int		i;
	char	**str_split;

	i = 1;
	str_split = ft_split(str, ' ');
	if (!export_mode(str_split) || ft_strchr(str, '|')) //  && !p_mode(str, 'p')
	{
		free_2d(str_split);
		return (0);
	}
	while (str_split[i])
	{
		if (is_invalid_export_syntax(str_split, i))
		{
			ft_putstr_fd("Error: Invalid export syntax.\n", 2);
			free_2d(str_split);
			return (1);
		}
		i++;
	}
	free_2d(str_split);
	return (0);
}
