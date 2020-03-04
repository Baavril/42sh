/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:06:51 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/05 15:05:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H
# include <stdlib.h>

struct				s_qnode
{
	void			*data;
	struct s_qnode	*previous;
};

typedef struct		s_queue
{
	struct s_qnode	*rear;
	struct s_qnode	*front;
}					t_queue;

struct s_qnode		*queue_create_node(void *data);
void				*queue_front(t_queue *queue);
void				*queue_dequeue(t_queue *queue, void (*del)(void *));
void				queue_apply_to_each(t_queue *queue, void (*f)());
void				queue_delete(t_queue *queue, void (*del)());
void				queue_enqueue(t_queue *queue, void *data);
void				queue_sort(t_queue *queue, int (*cmp)(void *, void *));
void				queue_reverse_recursion(t_queue *queue);
_Bool				queue_isempty(const t_queue *queue);
void				queue_reverse(t_queue *queue);
size_t				queue_size(t_queue *queue);

#endif
