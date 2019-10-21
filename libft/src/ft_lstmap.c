/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:56:43 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 17:22:14 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

//t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
//{
//	t_list	*new;
//
//	new = NULL;
//	if (f && lst)
//	{
//		new = (t_list*)malloc(sizeof(t_list));
//		if (!new)
//			return (NULL);
//		new = f(lst);
//		new->next = ft_lstmap(lst->next, f);
//	}
//	return (new);
//}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*new_bot;

	if (lst)
	{
		if (!(new = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new = (*f)(new);
		new_bot = new;
	}
	else
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_bot = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new_bot = (*f)(new_bot);
		ft_lstadd_back(&new, new_bot);
	}
	return (new);
}
