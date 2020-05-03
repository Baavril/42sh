/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:08:13 by user42            #+#    #+#             */
/*   Updated: 2020/05/03 15:08:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpop(t_list **alist, void (*del)(void *, size_t))
{
	t_list	*to_pop;

	if (!alist || !*alist)
		return ;
	to_pop = *alist;
	*alist = (*alist)->next;
	ft_lstdelone(&to_pop, del);
}
