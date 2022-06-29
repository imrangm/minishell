/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:40:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/26 14:03:23 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char	*get_expanded(char *element)
// {
// 	int	i;
// 	int	q;

// 	i = 0;
// 	q = 0;
// 	while (element[i])
// 	{
// 		if (ft_isquote(element[i]) && !q)
// 			q = element[i];
// 		else if (q && element[i] == q)
// 			q = 0;
// 		else if (element[i] == '$' && (!q || q == DQUOTE))
// 		{
// 			if (element[i + 1]
// 				&& (ft_isalpha(element[i + 1])
// 				|| element[i + 1] == '_'
// 				|| element[i] == '?'))
// 			{

// 			}
// 		}
// 		i++;
// 	}
// }

// void	expander(char **elements, int element_count)
// {
// 	int		i;
// 	char	**expanded;

// 	i = 0;
// 	expanded = malloc(sizeof(char *) * (element_count + 1));
// 	while (elements[i])
// 	{
// 		expanded =
// 		i++;
// 	}
// }