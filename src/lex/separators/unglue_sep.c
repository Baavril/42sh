/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unglue_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 17:14:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "separators.h"
#include "error.h"

const struct s_separators	g_separators[] =
{
	{";"},
	{"\0"}
};

static char	*get_closest_sep(char *str, int *lsep)
{
	int	i;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	while (*(g_separators[i].sep))
	{
		ptr = ft_strstr(str, g_separators[i].sep);
		if (ptr && (!closest || (ptr < closest && closest)))
		{
			*lsep = ft_strlen(g_separators[i].sep);
			closest = ptr;
		}
		++i;
	}
	return (closest);
}

static char	*extend(char *prefix, char *ptr, size_t lprefix, int lsep)
{
	int	lsep_cpy;
	size_t	len;
	char	*new;

	lsep_cpy = lsep;
	len = ft_strlen(prefix) + 2;
	if (!(new = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strncpy(new, prefix, lprefix);
	new[lprefix] = ' ';
	while (lsep_cpy)
	{
		new[lprefix + lsep_cpy] = *ptr;
		--lsep_cpy;
		++ptr;
	}
	new[lprefix + lsep + 1] = ' ';
	ft_strcat(new, ptr);
	return (new);
}

int	unglue_sep(char **input)
{
	int	lsep;
	size_t	lprefix;
	char	*new;
	char	*ptr;

	new = *input;
	lprefix = 0;
	lsep = 0;
	while ((ptr = get_closest_sep(&new[lprefix + lsep], &lsep)))
	{
		lprefix = (size_t)(ptr - *input);
		if (!(new = extend(*input, ptr, lprefix, lsep)))
			return (e_cannot_allocate_memory);
		ft_memdel((void**)input);
		*input = new;
		lsep += 2;
	}
	return (e_success);
}
