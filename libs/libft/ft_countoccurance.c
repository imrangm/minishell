/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countoccurance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:21:40 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/11 17:31:09 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countoccurance(char *str, char c1, char c2, char c3)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == c1 || str[i] == c2)
			c++;
		i++;
	}
	return (c);
}
