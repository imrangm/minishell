/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 01:11:00 by nmadi             #+#    #+#             */
/*   Updated: 2021/10/09 14:56:32 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_digitcounter(int n)
{
	int		dc;

	dc = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		dc++;
	}
	return (dc);
}

static	int	ft_power(int n, int p)
{
	int		num;

	num = n;
	while (p > 1)
	{
		num *= n;
		p--;
	}
	return (num);
}

static	char	*ft_minchecker(char *strnum, int n)
{
	if (n < -2147483647)
	{
		strnum[0] = '-';
		strnum[1] = '2';
		strnum[2] = '1';
		strnum[3] = '4';
		strnum[4] = '7';
		strnum[5] = '4';
		strnum[6] = '8';
		strnum[7] = '3';
		strnum[8] = '6';
		strnum[9] = '4';
		strnum[10] = '8';
		strnum[11] = '\0';
		return (strnum);
	}
	else if (n > 0 && n < 10)
	{
		strnum[0] = n + '0';
		strnum[1] = '\0';
		return (strnum);
	}
	return (0);
}

static	char	*ft_strnum(char *strnum, int t, int i, int n)
{
	if (n < -2147483647)
		return (ft_minchecker(strnum, n));
	if (n == 0)
	{
		strnum[i] = '0';
		strnum[i + 1] = '\0';
		return (strnum);
	}
	if (n < 0)
	{
		strnum[i] = '-';
		i++;
		n *= -1;
	}
	if (n > 0 && n < 10)
		return (ft_minchecker(strnum, n));
	while (t != 1 / 10)
	{
		strnum[i] = (n / t) + '0';
		n %= t;
		t /= 10;
		i++;
	}
	strnum[i] = '\0';
	return (strnum);
}

char	*ft_itoa(int n)
{
	char	*strnum;
	int		i[3];

	i[0] = 0;
	i[1] = ft_digitcounter(n);
	i[2] = ft_power(10, i[1] - 1);
	if (n < 0)
		i[1] += 1;
	strnum = (char *) malloc(i[1] + 1 * sizeof(char));
	if (!strnum)
		return (0);
	if (n < 0)
	{
		n *= -1;
		if (n > 0 && n < 10)
		{
			strnum[0] = '-';
			strnum[1] = n + '0';
			strnum[2] = '\0';
			return (strnum);
		}
		else
			n *= -1;
	}
	return (ft_strnum(strnum, i[2], i[0], n));
}
