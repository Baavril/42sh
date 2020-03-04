/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:12:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/15 18:54:49 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <getopt.h>
#include "job.h"
#include "libft.h"
#include "error.h"
#include "builtins.h"
#include "ft_getopt.h"
#include "hash_module.h"
#include "htable_type_dispatcher.h"

/*
**     Alias Errors:
** .invalid alias name(code 1): Metachars are present in the alias-name of the
** 			alias you want to create (in a alias-name=alias-value argument).
** .not found(code 1): the alias name you wanted to check isn't an alias (in a
** 			alias-name argument).
** .invalid opt(code 2): "alias: usage: alias [-p] [name[=value] ... ]"
*/
t_htable		*g_alias = NULL;
extern int		g_optind;
extern int		g_opterr;
extern int		g_optopt;

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

static int		ft_new_alias(int ac, char **av, char *mes)
{
	char		*str;
	int			ret;
	int			i;

	ret = 0;
	i = g_optind;
	while (i < ac)
	{
		if ((str = ft_strchr(av[i], '=')))
		{
			*(str++) = '\0';
			if (ft_isvalid_aliasname(av[i]))
				ft_insert_alias(av[i], str);
			else if ((ret = 1))
				ft_dprintf(STDERR_FILENO,
					"%s: alias: %c: invalid alias name.\n", g_progname, av[i]);
		}
		else if (g_alias && (str = (char*)ft_get_entry(g_alias, av[i])))
			ft_printf(mes, av[i], str);
		else if ((ret = 1))
			ft_dprintf(STDERR_FILENO,
							"%s: alias: %s: not found.\n", g_progname, av[i]);
		i++;
	}
	return (ret);
}

static int		ft_parse_alias_opt(int ac, char **av)
{
	int		ret;
	int		opt_p;

	opt_p = 0;
	g_opterr = 0;
	g_optind = 1;
	while ((ret = ft_getopt(ac, av, "p")) > 0)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO,
				"%s: alias: -%c: invalid option.\n", g_progname, g_optopt);
			ft_dprintf(STDERR_FILENO,
					"alias: usage: alias [-p] [name[=value] ... ].\n");
			return (2);
		}
		if (ret == 'p')
			opt_p = 1;
	}
	return (opt_p);
}

int				cmd_alias(int ac, char **av)
{
	int			ret;
	char		*mes;

	mes = "%s='%s'\n";
	if (ac < 1)
		return (1);
	if (ac == 1)
	{
		ft_print_sortalias(mes);
		return (0);
	}
	if ((ret = ft_parse_alias_opt(ac, av)) == 1)
	{
		mes = "alias %s='%s'\n";
		ft_print_sortalias(mes);
	}
	else if (ret == 2)
		return (2);
	ret = ft_new_alias(ac, av, mes);
	return (ret);
}
