/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 18:31:11 by tgouedar         ###   ########.fr       */
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

static char	*ft_dupslash(char **tokens, int j, int i, int ret)
{
	char	*tmp;

	tmp = NULL;
	if (j >= 0)
	{
		if (!ret)
		{
			tmp = ft_strdup((*tokens) + i);
		}
		else
			tmp = ft_strdup((*tokens) + j + 1);
	}
	ft_strdel(tokens);
	return (tmp);
}

char		*ft_set_slashed(char **tokens)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (*((*tokens) + i) && *((*tokens) + i) == BSLASH)
		++i;
	j = i;
	if (j % 2)
	{
		j--;
		ret = -1;
	}
	j /= 2;
	return (ft_dupslash(tokens, j, i, ret));
}

int			ft_back_slashed(char **tokens)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (*((*tokens) + i) && *((*tokens) + i) == BSLASH)
	{
		++i;
	}
	j = i;
	if (j % 2)
	{
		j--;
		ret = -1;
	}
	j /= 2;
	if (!ret && i)
		ret = j;
	return (ret);
}

char		*ft_setbslash(char *tokens, int nb)
{
	int		i;
	char	*tmp;
	char	*keep;

	i = 0;
	keep = NULL;
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (nb + 1))))
		return (NULL);
	while (nb > 0)
	{
		*(tmp + i++) = BSLASH;
		--nb;
	}
	keep = ft_strjoin(tmp, tokens);
	ft_strdel(&tmp);
	ft_strdel(&tokens);
	return (keep);
}
