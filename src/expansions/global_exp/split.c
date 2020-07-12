/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/07/12 22:19:04 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int		exp_limit(char *tokens)
{
	int	i;

	i = 0;
	if (*tokens == BSLASH)
		i++;
	++tokens;
	while (*tokens)
	{
		if (*tokens == BSLASH && *(tokens - 1) != BSLASH)
			i++;
		else if (*tokens == DOLLAR && *(tokens - 1) != BSLASH)
			i++;
		++tokens;
	}
	return (i);
}

int		malexps(char **dest, char *src)
{
	int		r;

	r = 0;
	if (!(*src))
	{
		*dest = ft_strdup("");
		return (0);
	}
	while (src[r] == DOLLAR || src[r] == BSLASH)
		++r;
	while (src[r] && !(src[r] == DOLLAR || src[r] == BSLASH))
		++r;
	if (!(*dest = (char*)ft_memalloc(sizeof(char) * (r + 1))))
		return (0);
	r = 0;
	while (*src == DOLLAR || *src == BSLASH)
		(*dest)[r++] = *(src++);
	while (*src && !(*src == DOLLAR || *src == BSLASH))
		(*dest)[r++] = *(src++);
	return (r);
}

/*
** nb +- 1 si '\' ligne 78 : nb = exp_limit(str) + 1;
*/

char	**ft_expsplit(char *str)
{
	int		i;
	int		nb;
	int		len;
	char	**tab;

	i = 0;
	len = 0;
	nb = exp_limit(str) + 1;
	if (nb == 0)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	while (i < nb)
		len += malexps(&(tab[i++]), str + len);
	tab[nb] = NULL;
	return (tab);
}
