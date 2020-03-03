/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/03 19:53:56 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
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

char	*malexps(char *str, int *len, char c)
{
	int		r;
	int		s;
	char	*ret;

	r = 0;
	s = 0;
	while ((str[*len + r] == c || str[*len + r] == BSLASH) && str[*len])
		++r;
	while (!(str[*len + r] == c || str[*len + r] == BSLASH)
	&& str[*len + r] && str[*len])
		++r;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (r + 1))))
		return (NULL);
	r = 0;
	while ((str[*len + r] == c || str[*len + r] == BSLASH) && str[*len])
		ret[s++] = str[*len + r++];
	while (!(str[*len + r] == c || str[*len + r] == BSLASH)
	&& str[*len + r] && str[*len])
		ret[s++] = str[*len + r++];
	*len += r;
	return (ret);
}

/*
** nb +- 1 si '\' ligne 78 : nb = exp_limit(str) + 1;
*/

char	**ft_expsplit(char *str, char c)
{
	int		i;
	int		nb;
	int		len;
	char	**tab;

	i = 0;
	nb = exp_limit(str) + 1;
	if (nb == 0)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	len = 0;
	while (i < nb)
		tab[i++] = malexps(str, &len, c);
	tab[nb] = 0;
	return (tab);
}
