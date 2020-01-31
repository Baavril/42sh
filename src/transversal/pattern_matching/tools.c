/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

int			check_next_var(char *var, char **token, int flag)
{
	if (!(ft_isalnum(token[0][(int)ft_strlen(var) + flag])
	|| token[0][(int)ft_strlen(var) + flag] == UNDERSCORE))
		return (SUCCESS);
	return (ERROR);
}

char		*setasvar(char *token)
{
	char	*ret;
	char	*var;
	char	*word;

	if (!(var = ft_strcdup(token + 2, COLON)))
		return (NULL);
	word = ft_strcdup(ft_strchr(token, EQUAL), CL_BRACE);
	ret = ft_strjoin(var, word);
	ft_strdel(&word);
	ft_strdel(&var);
	return (ret);
}

char		*ft_alpharange(char c, char x)
{
	int		i;
	int		lim;
	char	*ret;

	i = 0;
	ret = NULL;
	lim = (x - c) + 1;
	if (lim > 1)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (lim + 1))))
			return (0);
		while (i < lim)
			ret[i++] = c++;
		ret[i] = '\0';
	}
	return (ret);
}

static char	*ft_struchr(char *match, int len)
{
	int i;
	int j;
	char *ret;

	j = 0;
	i = 1;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[0] = match[1];
	while (match[i] && match[i] != CL_SQUAR)
	{
		j = 0;
		while (ret[j])
		{
			if ((ret[j] - match[i]) == 0)
				break;
			if (ret[j + 1] == '\0')
				ret[j + 1] = match[i];
			++j;
		}
		++i;
	}
	return (ret);
}

char		*ft_strneg(char *match)
{
	int		j;
	int		c;
	char	*tmp;
	char	*strneg;
	char	*strpos;

	j = 0;
	c = 32;
	strpos = ft_struchr(match, ft_strlen(match));
	tmp = strpos;
	if (!(strneg = (char*)ft_memalloc(sizeof(char) * MAXCHR)))
		return (NULL);
	while (*strpos && c < 127)
	{
		if ((*strpos - c) == 0)
		{
			++strpos;
			++c;
		}
		else
			strneg[j++] = c++;
	}
	while (c < 127)
		strneg[j++] = c++;
	ft_strdel(&tmp);
	return (strneg);
}
