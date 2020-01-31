/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2019/12/03 16:21:55 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"

struct s_svar	*g_svar;
struct s_pos	*g_pos;

static int		ft_retinstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] - c == 0)
			return (i);
		i++;
	}
	return (1);
}

char			*ft_strdupfm(char *str, char c)
{
	int		i;
	int		lim;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	lim = ft_retinstr(str, c) + 1;
	if (len - lim >= 0)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (len - lim) + 1)))
			return (NULL);
		len = len - lim;
	}
	else
		return (NULL);
	while (len)
	{
		ret[i] = str[lim];
		len--;
		i++;
		lim++;
	}
	ret[i] = '\0';
	return (ret);
}

char			*ft_strdupto(char *str, char c)
{
	int		i;
	int		lim;
	char	*ret;

	i = 0;
	lim = ft_retinstr(str, c) + 1;
	if (!(ret = (char*)malloc(sizeof(char) * (lim + 1))))
		return (NULL);
	while (i < lim)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
