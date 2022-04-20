/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:09:07 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 09:53:08 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = (*lst);
	while (ptr != NULL)
	{
		temp = ptr;
		(del)(temp->content);
		ptr = ptr->next;
		free(temp);
	}
	(*lst) = NULL;
}
