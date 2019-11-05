/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:09:58 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/22 14:15:20 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

struct	s_stack
{
	struct s_stack	*previous;
	void		*data;	
};

struct s_stack	*stack_create_element(void *data);
struct s_stack	*stack_initialize(void *data);
void			stack_push(struct s_stack **top, void *data);
void			stack_pop(struct s_stack **top, void (*del_data)(void *));
void 			*stack_pop_get_data(struct s_stack **top);
void			*stack_peek(struct s_stack **top);
void			stack_swap(struct s_stack **top);
void			stack_delete(struct s_stack **top, void (*del_data)(void *));
void			stack_apply_to_each(struct s_stack **top, void (*f)());
void			stack_reverse(struct s_stack **top);
void			stack_reverse_recursion(struct s_stack **top);
void			stack_duplicate(struct s_stack **top, void *(*copy_data)());
void			stack_sort(struct s_stack **top, int (*cmp)(void *, void *));
_Bool			stack_isempty(struct s_stack **top);

#endif