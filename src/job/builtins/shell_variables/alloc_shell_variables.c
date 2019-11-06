/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:50:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 16:51:12 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

struct s_shvar	*create_shvar_node(char *value, struct s_shvar *next_content,
						struct s_shvar *next_var, int index)
{
	struct s_shvar	*node;

	node = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->next_content = next_content;
	node->next_var = next_var;
	node->index = index;
	if (index != -1)
		node->isarray |= 1;
	return (node);
}