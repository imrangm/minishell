/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:50:14 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/07 15:08:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_sign(int n)
{
	if (n < 0)
	{
		n = n * (-1);
		return (1);
	}
	else
		return (0);
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	int		sign;
	char	*a;

	i = ft_numlen(n);
	j = i;
	sign = ft_sign(n);
	if (sign)
		n = n * -1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	a = (char *) malloc ((i + sign + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	while (i-- > 0)
	{
		a[i + sign] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign)
		a[0] = '-';
	a[j + sign] = '\0';
	return (a);
}
