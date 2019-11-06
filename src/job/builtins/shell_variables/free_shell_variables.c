/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:06:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

static void	free_nodes(struct s_shvar **node)
{
	struct s_shvar	*stofree;

	stofree = *node;
	while (stofree)
	{
		*node = stofree;
		stofree = (*node)->next_content;
		ft_memdel((void**)&(*node)->value);
		ft_memdel((void**)node);
	}
}
/* For UNSET builtin use or set that erase preivously stored value
static void	free_a_shvar(struct s_shvar **previous, struct s_shvar **node)
{
	if (!*previous)
	{
		if (!(*node)->next_var)
			g_shellvar = NULL;
		else
			g_shellvar = (*node)->next_var;
	}
	else
	{
		if (!(*node)->next_var)
			(*previous)->next_var = NULL;
		else
			(*previous)->next_var = (*node)->next_var;
	}
	free_nodes(node);
}
*/
static void	free_all_tree(struct s_shvar **tree)
{
	struct s_shvar	*ltofree;

	if (*tree)
	{
		ltofree = *tree;
		while (ltofree)
		{
			*tree = ltofree;
			ltofree = (*tree)->next_var;
			free_nodes(tree);
		}
	}
}

void		free_all_shvar(void)
{
	extern struct s_shvar *g_shellvar;

	free_all_tree(&g_shellvar);
}
