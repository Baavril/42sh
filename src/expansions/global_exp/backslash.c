/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/07/17 15:16:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

static char	*dup_slash(char **tokens, int j, int i, int ret)
{
	char	*tmp;

	tmp = NULL;
	if (i > 0)
	{
		if (!ret)
		{
			tmp = ft_strdup((*tokens) + i);
			ft_strdel(tokens);
			return (tmp);
		}
		else
		{
			tmp = ft_strdup((*tokens) + j + 1);
			ft_strdel(tokens);
			return (tmp);
		}
	}
	return (*tokens);
}

static char	*dup_hdc_slash(char **tokens, int j, int i)
{
	char	*tmp;

	tmp = NULL;
	if (i > 0)
	{
		tmp = ft_strdup((*tokens) + (i - j));
		ft_strdel(tokens);
		return (tmp);
	}
	return (*tokens);
}

char		*set_slash(char **tokens, int flag)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while ((*tokens)[i] == BSLASH)
		++i;
	ret = i % 2;
	j = i / 2;
	if (flag)
		return (dup_hdc_slash(tokens, j, i));
	return (dup_slash(tokens, j, i, ret));
}

int			back_slashed(char **tokens)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while ((*tokens)[i] == BSLASH)
		++i;
	j = i;
	if (j % 2)
	{
		--j;
		ret = -1;
	}
	j /= 2;
	if (!ret && i)
		ret = j;
	return (ret);
}

char		*set_back_slash(char *tokens, int nb)
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
