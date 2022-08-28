/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/27 13:48:45 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * empty file to include addtl functions *//

int	check_io(char *prev, char *current)
{
	return (((ft_strncmp(prev, DGREAT, 2) == 0
				|| ft_strncmp(prev, GREAT, 1) == 0)
			&& ((ft_strncmp(current, DLESS, 2) == 0)
				|| (ft_strncmp(current, LESS, 1) == 0)))
		|| ((ft_strncmp(prev, DLESS, 2) == 0
				|| ft_strncmp(prev, LESS, 1) == 0)
			&& ((ft_strncmp(current, DGREAT, 2) == 0)
				|| (ft_strncmp(current, GREAT, 1) == 0))));
}
