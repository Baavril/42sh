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
			ret = j;
		}
		else
			tmp = ft_strdup((*tokens) + j + 1);
	}
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
		++i;
	j = i;
	if (j % 2)
	{
		j--;
		ret = -1;
	}
	j /= 2;
	return (ret);
}

int			ft_setbslash(char **tokens, int nb)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (nb + 1))))
		return (0);
	while (nb > 0)
	{
		*(tmp + i++) = BSLASH;
		--nb;
	}
	tmp = ft_strjoin(tmp, *tokens);
	free(*tokens);
	*tokens = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (SUCCESS);
}
