/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:13:25 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 19:32:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


#include "job.h"
#include "libft.h"
#include "error.h"
#include "hash_module.h"
#include "htable_type_dispatcher.h"

t_htable		*g_bintable = NULL;

int				ft_inbintable(char **bin_name)
{
	t_bash_hash		*value;

	if ((g_bintable) && (value = ft_get_entry(g_bintable, *bin_name)))
	{
		value->hit_value++;
		*bin_name = ft_strdup(value->bin_path);
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
	if (!ft_get_entry(g_bintable, bin_name))
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
		ret += ft_find_and_hash(av[i]);
		i++;
	}
	return (ret > 0 ? 1 : 0);
}
