/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:13:27 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/12 17:40:22 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nart.h"

int	is_valid(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			printf("Error: Backslashes are not permitted.\n");
			return (0);
		}
		else if (str[i] == ';')
		{
			printf("Error: Semicolons are not permitted.\n");
			return (0);
		}
		else if (str[i] == '\'')
			quote_count++;
		i++;
	}
	if (quote_count % 2)
	{
		printf("Error: Unclosed quotes are not permitted.\n");
		return (0);
	}
	return (1);
}