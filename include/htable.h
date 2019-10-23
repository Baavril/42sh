/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:33:05 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 19:02:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
# define HTABLE_H

# include <stdint.h>
# include "libft.h"

# define LIST_SIZE			16
# define ALPH_PRIME			269
# define GOOD_ENOUGH		6

union				u_rd
{
	char			rd[8];
	uint64_t		nbr;
};

typedef struct		s_bash_hash
{
	char			*bin_path;
	unsigned int	hit_value;
}					t_bash_hash;

typedef struct		s_entry
{
	char			*key;
	void			*value;
	size_t			value_size;
}					t_entry;

typedef struct		s_hlist
{
	t_entry			*content;
	size_t			content_size;
	struct s_hlist	*next;
}					t_hlist;

typedef struct		s_htable
{
	t_hlist			**table;
	uint64_t		table_size;
	uint64_t		entry_nbr;
	uint64_t		big_prime;
	uint64_t		ran_a;
	uint64_t		ran_b;
	int				data_type;
}					t_htable;

typedef void		(*t_ft_list)(t_list *);
typedef void		(*t_ft_free)(void *, size_t);
typedef t_list		*(*t_ft_lstcpy)(t_list *);

uint64_t			ft_hash(const t_htable *htable, const char *to_hash);
uint64_t			ft_get_prime(uint64_t min);
uint64_t			ft_get_ran(uint64_t mod);
int					ft_miller_rabin(uint64_t to_test, uint64_t k);
void				ft_del_entry(t_hlist **alst, void (*del)(void *, size_t));
t_hlist				*ft_lst_entries(const t_htable *htable);
t_ft_lstcpy			ft_get_lstcpy(int e_table_type);
t_ft_list			ft_get_lstprint(int e_table_type);
t_ft_free			ft_get_free(int e_table_type);
size_t				ft_get_value_size(int e_table_type, void *value);
t_list				*ft_bash_lstcpy(t_list *elem);
t_list				*ft_string_lstcpy(t_list *elem);
void				ft_print_string(t_list *to_print);
void				ft_print_bash(t_list *to_print);
void				ft_free_string(void *to_free, size_t null);
void				ft_free_bash(void *to_free, size_t null);

#endif
