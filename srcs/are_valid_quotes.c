/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_valid_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:22:03 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/22 17:08:02 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	are_valid_quotes(char *str)
// {
// 	int	i;
// 	int	single_quote_count;
// 	int	db_quote_mode;

// 	i = 0;
// 	single_quote_count = 0;
// 	db_quote_mode = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && !db_quote_mode)
// 			db_quote_mode = 1;
// 		else if (str[i] == '\"' && db_quote_mode)
// 			db_quote_mode = 0;
// 		if (str[i] == '\'' && !db_quote_mode)
// 			single_quote_count++;
// 		i++;
// 	}
// 	if (single_quote_count % 2 || double_quote_count % 2)
// 	{
// 		ft_putstr_fd("Error: Unclosed quotes are not permitted.\n",
// 			2);
// 		return (0);
// 	}
// 	return (1);
// }
