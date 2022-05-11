/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_atoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:55:37 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 18:32:38 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

int	m_atoi(const char *str)
{
	int					i;
	long long	result;
	long long int		neg;

	i = 0;
	neg = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i++] - '0');
		if (result < -2147483648 || result > 2147483647)
			return (-1);
	}
	return (result * neg);
}
