/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:28:01 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/06 16:34:42 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list*)ft_memalloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
		return (new);
	new->content = malloc(content_size);
	ft_memcpy(new->content, content, content_size);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->content_size = content_size;
	new->next = NULL;
	return (new);
}
