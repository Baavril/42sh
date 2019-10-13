/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:34:59 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 05:20:06 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_part_list(t_list *lst_start, t_list **new_head)
{
	t_list		*slow;
	t_list		*fast;

	if (!(lst_start) || !(lst_start->next))
	{
		*new_head = NULL;
		return ;
	}
	slow = lst_start;
	fast = lst_start->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*new_head = slow->next;
	slow->next = NULL;
}

static t_list		*ft_merge_list(t_list *lst1, t_list *lst2, t_ft_cmp ft_cmp)
{
	t_list		*new_lst;

	if (!(lst1))
		return (lst2);
	if (!(lst2))
		return (lst1);
	if (ft_cmp(lst1, lst2) > 0)
	{
		new_lst = lst1;
		new_lst->next = ft_merge_list(lst1->next, lst2, ft_cmp);
	}
	else
	{
		new_lst = lst2;
		new_lst->next = ft_merge_list(lst1, lst2->next, ft_cmp);
	}
	return (new_lst);
}

void				ft_lst_mergesort(t_list **lst, t_ft_cmp ft_cmp)
{
	t_list		*head;
	t_list		*mid;

	if ((*lst) && ((*lst)->next))
	{
		head = *lst;
		ft_part_list(*lst, &mid);
		ft_lst_mergesort(&head, ft_cmp);
		ft_lst_mergesort(&mid, ft_cmp);
		*lst = ft_merge_list(head, mid, ft_cmp);
	}
}
