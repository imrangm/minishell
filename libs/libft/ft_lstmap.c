/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:34:24 by imustafa          #+#    #+#             */
/*   Updated: 2021/10/11 13:26:22 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	temp = ft_lstnew((f)(lst->content));
	if (temp == NULL)
		return (NULL);
	newlst = temp;
	lst = lst->next;
	while (lst != NULL)
	{
		temp = ft_lstnew((f)(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, temp);
	}
	return (newlst);
}
