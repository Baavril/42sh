/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:45:27 by tgouedar          #+#    #+#             */
/*   Updated: 2019/11/04 16:17:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "job.h"
#include "libft.h"
#include "error.h"
#include "builtins.h"
#include "hash_module.h"
#include "htable_type_dispatcher.h"

/*
**     Alias Errors:
** .invalid alias name(code 1): Metachars are present in the alias-name of the
** 			alias you want to create (in a alias-name=alias-value argument).
** .not found(code 1): the alias name you wanted to check isn't an alias (in a
** 			alias-name argument).
** .invalid opt(code 2): "alias: usage: alias [-p] [name[=value] ... ]"
**
**     Unalias Errors:
** .no_arg(code 2): usage. "unalias: usage: unalias [-a] name [name ...]"
** .not found(code 1): the alias-name is not associated with an alias
*/

t_htable		*g_alias = NULL;

void				ft_treat_alias(char **first_arg)
{
	char	*value;

	if (!g_alias)
		return ;
	if ((value = ft_get_entry(g_alias, *first_arg)))
	{
		ft_strdel(first_arg);
		*first_arg = ft_strdup(value);
	}
}

static void			ft_insert_alias(char *alias_name, char *alias_value)
{
	if (!(g_alias))
	{
		g_alias = ft_memalloc(sizeof(t_htable));
		*g_alias = ft_init_htable(2, e_string_entries);
	}
	ft_insert(g_alias, alias_name, alias_value);
}

void			ft_free_aliastable(void)
{
	if (g_alias)
	{
		ft_free_htable(g_alias);
		free(g_alias);
	}
}

int			cmd_unalias(int ac, char **av)
{
	_Bool		ret;
	int			i;

	if (ac == 1)
	{
		ft_dprintf(STDERR_FILENO, "unalias: usage: unalias [-a] name [name ...]");
		return (2);
	}
	i = 0;
	ret = 0;
	while (i < ac)
	{
		if (!ft_del_entry(g_alias, av[i]))
		{
				ft_dprintf(STDERR_FILENO, "notfound");
			ret |= 1;
		}
		i++;
	}
	return (ret);
}

int			ft_isvalid_aliasname(char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (ft_isin(name[i], UNVALID_ALIAS))
			return (0);
		i++;
	}
	return ((i > 0));
}

int			cmd_alias(int ac, char **av)
{
	int			i;
//	int			j;
	_Bool		ret;
	char		*str;
	char		*mes;

	if (ac < 1)
		return (1);
	if (ac == 1)
	{
		if (g_alias)
			ft_print_sortentries(g_alias);
		return (0);
	}
	
	i = 1;
	ret = 0;
	mes = "%s='%s'\n";
//	/**gestion de l'option: peut etre edulcoree ? */
//	while (av[i] && av[i][0] == '-' && (ft_strcmp(av[i], "--") || (i++)))
//	{
//		j = 1;
//		while (av[i][j])
//		{
//			if (av[i][j] == 'p')
//			{
//				mes = "alias %s='%s'\n";
//				ret = 1;
//			}
//			else
//			{
//				ft_dprintf(STDERR_FILENO, "alias: usage: alias [-p] [name[=value] ... ]");
//				return (2);
//			}
//			j++;
//		}
//		i++;
//	}
//	if (ret && !(ret = 0) && g_alias)
//	ft_print_sortentries(g_alias);
//
//	/* Fin de gestion de l'option */

	/* Gestion des arguments */

	while (i < ac)
	{
		if ((str = ft_strchr(av[i], '=')))
		{
			*(str++) = '\0';
			if (ft_isvalid_aliasname(av[i]))
				ft_insert_alias(av[i], str);
			else if ((ret = 1))
				ft_dprintf(STDERR_FILENO, "invalid alias name");
		}
		else if (g_alias && (str = (char*)ft_get_entry(g_alias, av[i])))
			ft_printf(mes, av[i], str);
		else
		{
				ft_dprintf(STDERR_FILENO, "notfound");
			ret |= 1;
		}
		i++;
	}
	return (ret);
}
