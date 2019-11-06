/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:13:25 by tgouedar          #+#    #+#             */
/*   Updated: 2019/11/06 18:11:39 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "libft.h"
#include "error.h"
#include "hash_module.h"
#include "htable_type_dispatcher.h"

/*
**                   <>>> ABSTRACT FROM POSIX MAN <<<>
**
**        hash -- remember or report utility locations
** 
** SYNOPSIS
** 
**        hash [utility...]
** 
**        hash -r
** 
** DESCRIPTION
** 
**        The hash utility shall affect the way the current shell environment
** remembers the locations of utilities found as described in Section 2.9.1.1, 
** Command Search and Execution. Depending on the arguments specified, it shall
** add utility locations to its list of remembered locations or it shall purge
** the contents of the list. When no arguments are specified, it shall report
** on the contents of the list.
** 
**        Utilities provided as built-ins to the shell shall not be reported by
** hash.
** 
** OPTIONS
** 
**        The hash utility shall conform to the Base Definitions volume of
** POSIX.1-2008, Section 12.2, Utility Syntax Guidelines.
** 
**        The following option shall be supported:
** 
**        -r : Forget all previously remembered utility locations.
** 
** OPERANDS
** 
**        The following operand shall be supported:
** 
**        [utility_name] : The name of a utility to be searched for and added
** to the list of remembered locations. If utility contains one or more <slash>
** characters, the results are unspecified.
*/

t_htable		*g_bintable = NULL;

int				ft_inbintable(char *bin_name, char **ret_val, char flag)
{
	t_bash_hash		*value;

	if ((g_bintable) && (value = ft_get_entry(g_bintable, bin_name)))
	{
		if (ret_val)
			*ret_val = ft_strdup(value->bin_path);
		if (flag == HIT)
			value->hit_value++;
		return (1);
	}
	return (0);
}

void			ft_insert_bintable(char *bin_name, char *bin_path,
														unsigned int hit_val)
{
	if (!(g_bintable))
	{
		g_bintable = ft_memalloc(sizeof(t_htable));
		*g_bintable = ft_init_htable(DEF_SIZE, e_bash_entries);
	}
	ft_insert_bash(g_bintable, bin_name, bin_path, hit_val);
}

void			ft_free_bintable(void)
{
	if (g_bintable)
	{
		ft_free_htable(g_bintable);
		free(g_bintable);
	}
}

static int		ft_find_and_hash(char *bin_name)
{
	char	*bin_path;
	char	*error_text;

	bin_path = ft_strdup(bin_name);
	if (path_concat(&bin_path) == e_command_not_found)
	{
		error_text = ft_strjoin("hash: ", bin_name);
		psherror(e_not_found, error_text, e_builtin_type);
		free(error_text);
		return (1);
	}
	ft_insert_bintable(bin_name, bin_path, NO_HIT);
	return (0);
}

int				cmd_hash(int ac, char **av)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (g_bintable == NULL)
	{
		g_bintable = ft_memalloc(sizeof(t_htable));
		*g_bintable = ft_init_htable(DEF_SIZE, e_bash_entries);
	}
	if (ac > 1 && !ft_strcmp(av[i], "-r"))
	{
		ft_empty_htable(g_bintable);
		i++;
	}
	if (ac == 1 && g_bintable->entry_nbr != 0)
	{
		ft_putendl("hits   command");
		ft_print_sortentries(g_bintable);
	}
	while (i < ac)
	{
		ret |= ft_find_and_hash(av[i]);
		i++;
	}
	return (ret);
}
