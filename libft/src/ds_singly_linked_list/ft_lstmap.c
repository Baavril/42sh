/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:56:43 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/06 16:34:42 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	new = NULL;
	if (f && lst)
	{
		new = ft_lstnew(lst->content, lst->content_size);
		if (!new)
			return (NULL);
		new = f(lst);
		new->next = ft_lstmap(lst->next, f);
	}
	return (new);
}
