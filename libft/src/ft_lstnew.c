/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:28:01 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 17:24:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

//t_list	*ft_lstnew(void const *content, size_t content_size)
//{
//	t_list	*new;
//
//	new = (t_list*)malloc(sizeof(t_list));
//	if (!new)
//		return (NULL);
//	if (!content)
//	{
//		new->content = NULL;
//		new->content_size = 0;
//		new->next = NULL;
//		return (new);
//	}
//	new->content = ft_strdup(content);
//	if (!new->content)
//	{
//		free(new);
//		return (NULL);
//	}
//	new->content_size = content_size;
//	new->next = NULL;
//	return (new);
//}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *o;

	if (!(o = (t_list*)malloc(sizeof(*o))))
		return (NULL);
	if (content == NULL)
	{
		o->content = NULL;
		o->content_size = 0;
	}
	else
	{
		if (!(o->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(o->content, content, content_size);
		o->content_size = content_size;
	}
	o->next = NULL;
	return (o);
}
