//42header

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
