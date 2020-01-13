/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:09:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 15:08:02 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

typedef struct		s_stack
{
	struct s_stack	*previous;
	void			*data;
}					t_stack;

t_stack				*stack_create_element(void *data);
t_stack				*stack_initialize(void *data);
void				stack_push(t_stack **top, void *data);
void				stack_pop(t_stack **top, void (*del_data)(void *));
void				*stack_pop_get_data(t_stack **top);
void				*stack_peek(t_stack **top);
void				stack_swap(t_stack **top);
void				stack_delete(t_stack **top, void (*del_data)(void *));
void				stack_apply_to_each(t_stack **top, void (*f)());
void				stack_reverse(t_stack **top);
void				stack_reverse_recursion(t_stack **top);
void				stack_duplicate(t_stack **top, void *(*copy_data)());
void				stack_sort(t_stack **top, int (*cmp)(void *, void *));
_Bool				stack_isempty(t_stack **top);

#endif
