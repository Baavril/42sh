/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unglue_metachr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/29 19:43:39 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"
#include "pipelines.h"

static char	*get_closest_meta(char *str, int *lsep)
{
	const struct s_metachr	metachr[] =
	{ {"||"}, {"&&"}, {"&>"}, {">&"}, {";;"}, {"|&"},
		{"<<"}, {">>"}, {"<"}, {">"}, {";"}, {"&"}, {"\0"} };
	char					*closest;
	char					*ptr;
	int						i;

	i = 0;
	closest = NULL;
	while (*(metachr[i].c))
	{
		ptr = ft_strstr(str, metachr[i].c);
		if (ptr && (!closest || (ptr < closest && closest)))
		{
			*lsep = ft_strlen(metachr[i].c);
			closest = ptr;
		}
		++i;
	}
	return (closest);
}

static char	*extend(char *prefix, char *ptr, size_t lprefix, int lsep)
{
	int		lsep_cpy;
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

int			unglue_metachr(char **input)
{
	int		lsep;
	size_t	lprefix;
	char	*new;
	char	*ptr;

	new = *input;
	lprefix = 0;
	lsep = 0;
	while ((ptr = get_closest_meta(&new[lprefix + lsep], &lsep)))
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
