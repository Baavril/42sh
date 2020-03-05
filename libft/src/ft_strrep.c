/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:43:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:05:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_strrep.h"

static int	count_expansion_instances(char *dst, const char *expansion)
{
	int	nb;

	nb = 0;
	while (*dst && (dst = ft_strstr(dst, expansion)))
	{
		++nb;
		++dst;
	}
	return (nb);
}

static char	*malloc_new_line(char *dst, const char *content,
		const char *expansion, int instances)
{
	char	*new;
	size_t	ldst;
	size_t	lcontent;
	size_t	lexpansion;

	ldst = ft_strlen(dst);
	lcontent = ft_strlen(content);
	lexpansion = ft_strlen(expansion);
	if (!(new = (char*)ft_memalloc(sizeof(char)
					* (instances * (lcontent - lexpansion) + ldst + 1))))
		return (NULL);
	else
		return (new);
}

static void	wh_build(struct s_strrep *rep)
{
	if ((rep->ptr = ft_strstr(rep->dst, rep->expansion)))
		rep->content_cpy = (char*)rep->content;
	rep->expansion_cpy = (char*)rep->expansion;
	while (rep->dst < rep->ptr || (!rep->ptr && *(rep->dst)))
	{
		*(rep->cpy) = *(rep->dst);
		++rep->dst;
		++rep->cpy;
	}
	while (*(rep->dst) && *(rep->expansion_cpy))
	{
		++rep->dst;
		++rep->expansion_cpy;
	}
	while (*(rep->content_cpy))
	{
		*(rep->cpy) = *(rep->content_cpy);
		++(rep->cpy);
		++(rep->content_cpy);
	}
	rep->ptr = NULL;
}

static void	build_str(char *dst, const char *content,
		const char *expansion, char *cpy)
{
	struct s_strrep	rep;

	rep.ptr = NULL;
	rep.dst = dst;
	rep.content = content;
	rep.expansion = expansion;
	rep.cpy = cpy;
	rep.content_cpy = NULL;
	while (*rep.dst || rep.ptr)
		wh_build(&rep);
}

char		*ft_strrep(char **dst, const char *content, const char *expansion)
{
	char	*cpy;
	int		instances;

	if (!expansion || !content || !dst)
		return (NULL);
	instances = count_expansion_instances(*dst, expansion);
	if (!instances)
		return (*dst);
	if (!(cpy = malloc_new_line(*dst, content, expansion, instances)))
		return (NULL);
	build_str(*dst, content, expansion, cpy);
	free(*dst);
	*dst = cpy;
	return (*dst);
}
