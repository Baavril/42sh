/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:58:08 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 12:04:10 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (del && *alst)
	{
		ft_lstdel(&((*alst)->next), del);
		del((*alst)->content, (*alst)->content_size);
		ft_memdel((void**)alst);
	}
}
