/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:12:54 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/13 10:19:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable_type_dispatcher.h"
#include "hash_module.h"
#include "builtins.h"

extern t_htable		*g_alias;

void				ft_free_aliastable(void)
{
	if (g_alias)
	{
		ft_free_htable(g_alias);
		free(g_alias);
	}
}

void				ft_insert_alias(char *alias_name, char *alias_value)
{
	if (!(g_alias))
	{
		g_alias = ft_memalloc(sizeof(t_htable));
		*g_alias = ft_init_htable(2, e_string_entries);
	}
	ft_insert(g_alias, alias_name, alias_value);
}

int					ft_isvalid_aliasname(char *name)
{
	size_t		i;

	i = 0;
	while (name[i])
	{
		if (ft_isin(name[i], UNVALID_ALIAS))
			return (0);
		i++;
	}
	return ((i > 0));
}

char				*ft_get_alias(char *alias_name)
{
	char	*str;

	if (!g_alias)
		return (NULL);
	if ((str = ft_get_entry(g_alias, alias_name)))
		return (ft_strdup(str));
	return (NULL);
}
