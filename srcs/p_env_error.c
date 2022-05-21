/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:09:27 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/21 18:15:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_consecutive_equal_signs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if (str[i] == '=' && str[i + 1] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

int	p_env_error(char *str)
{
	int		i;
	char	**str_split;

	i = 1;
	str_split = ft_split(str, ' ');
	if (cmp_str(str_split[0], "export"))
	{
		ft_free_arg(str_split);
		return (0);
	}
	while (str_split[i])
	{
		if (contains_consecutive_equal_signs(str_split[i])
			|| !ft_strncmp(str_split[i], "=", ft_strlen(str_split[i]))
			|| ft_isdigit(str_split[i][0])
			|| str_split[i][ft_strlen(str_split[i]) - 1] == '=')
		{
			ft_free_arg(str_split);
			return (1);
		}
		i++;
	}
	ft_free_arg(str_split);
	return (0);
}