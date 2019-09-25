/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"
#include "expansions.h"

int	parameter_expansions(size_t *index, char **str, const char *opentag, const char *closetag)
{
	int	ret;

	size_t	lopen;
	size_t	lvarname;
	size_t	lclose;

	char	*rest;
	size_t	lrest;

	char	*content;
	size_t	lcontent;

	char	*new;

	lopen = ft_strlen(opentag);
	lvarname = ft_varlen(&(*str)[lopen], closetag);
	lclose = ft_strlen(closetag);


	rest = &(*str)[lopen + lvarname + lclose];
	lrest = ft_strlen(rest);

	if ((ret = getenv_content(&content, &(*str)[lopen], closetag)))
		return (ret);
	lcontent = ft_strlen(content);


	if (!(new = (char*)ft_memalloc(sizeof(char) * (lrest + lcontent + 1))))
	{
		ft_memdel((void**)&content);
		return (e_cannot_allocate_memory);
	}
	if (content)
		ft_strncat(new, content, lcontent);
	ft_memdel((void**)&content);
	ft_strncat(new, rest, lrest);


	*str = new;
	*index = lcontent;
	return (e_success);
}
