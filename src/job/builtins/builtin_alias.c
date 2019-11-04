/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:45:27 by tgouedar          #+#    #+#             */
/*   Updated: 2019/11/04 19:33:00 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <getopt.h>
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
extern int		optind;
extern int		opterr;

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
	int			ret;
	int			i;
	char		*opt;

	opt = "+a";
	opterr = 0;
	optind = 1;
	while ((i = getopt(ac, av, opt)) > 0)
	{
		if (i == '?' && (ret = 2))
			break ;
		if (i == 'a')
		{
			ft_empty_htable(g_alias);
			return (0);
		}
	}
	if (ac < 2 || ret == 2)
	{
		ft_dprintf(STDERR_FILENO, "unalias: usage: unalias [-a] name ... ]\n");
		return (2);
	}
	if (!g_alias)
		return (0);
	i = optind;
	ret = 0;
	while (i < ac)
	{
		if (!ft_del_entry(g_alias, av[i]))
		{
			ft_dprintf(STDERR_FILENO, "%s: unalias: %s: not found\n", g_progname, av[i]);
			ret |= 1;
		}
		i++;
	}
	return (ret);
}

int			ft_isvalid_aliasname(char *name)
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

static void		ft_print_sortalias(char *mes)
{
	t_list		*entries;
	t_list		*voyager;
	t_entry		*content;
	int			table_type;

	if (!g_alias)
		return ;
	table_type = g_alias->data_type;
	entries = (t_list*)ft_lst_entries(g_alias);
	ft_lst_mergesort(&entries, ft_get_lstcmp(table_type));
	voyager = entries;
	while (voyager)
	{
		content = voyager->content;
		ft_printf(mes, content->key, content->value);
		voyager = voyager->next;
	}
	ft_lstdel(&entries, ft_get_free(table_type));
}

int			cmd_alias(int ac, char **av)
{
	int			i;
	int			ret;
	char		*str;
	char		*mes;
	char		*opt;

	opt = "+p";
	mes = "%s='%s'\n";
	if (ac < 1)
		return (1);
	if (ac == 1)
	{
		ft_print_sortalias(mes);
		return (0);
	}
	opterr = 0;
	optind = 1;
	while ((ret = getopt(ac, av, opt)) > 0)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO, "alias: usage: alias [-p] [name[=value] ... ]\n");
			return (2);
		}
		if (ret == 'p')
		{
			mes = "alias %s='%s'\n";
			i = 1;
		}
	}
	if (i && !(ret = 0))
		ft_print_sortalias(mes);
	i = optind;
	while (i < ac)
	{
		if ((str = ft_strchr(av[i], '=')))
		{
			*(str++) = '\0';
			if (ft_isvalid_aliasname(av[i]))
				ft_insert_alias(av[i], str);
			else if ((ret = 1))
				ft_dprintf(STDERR_FILENO, "%s: alias: %c: invalid alias name\n", g_progname, av[i]);
		}
		else if (g_alias && (str = (char*)ft_get_entry(g_alias, av[i])))
			ft_printf(mes, av[i], str);
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: alias: %s: not found\n", g_progname, av[i]);
			ret |= 1;
		}
		i++;
	}
	return (ret);
}
