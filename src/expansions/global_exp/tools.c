/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_libft_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/22 18:40:52 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

char *ft_strcdup(char *token, char c)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	if (!token || !*token || *token == c)
		return (NULL);
	while (token[i] != c)
		++i;
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (token[i] != c)
	{
		ret[i] = token[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strpchr(char *str, char c)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len && str[i])
	{
		if (str[i] - c == 0)
			return (i);
		i++;
	}
	return (0);
}

int ft_spechrlen(char *token)
{
	int pos;

	if ((pos = ft_strpchr(token, SHARP)))
		return ((token[pos + 1] == SHARP)
				? SUCCESS : ERROR);
	if ((pos = ft_strpchr(token, PERCENT)))
		return ((token[pos + 1] == PERCENT)
				? SUCCESS : ERROR);
	return (ERROR);
}

int ft_strlncmp(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s1[i])
		++i;
	--i;
	while (s2[j])
		++j;
	--j;
	while (len > 0 && s1[i] && s2[j] && s1[i] == s2[j])
	{
		--len;
		--i;
		--j;
	}
	if (!len)
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

char *ft_strrev(char *token)
{
	int i;
	int len;
	char tmp;

	i = 0;
	len = ft_strlen(token) - 1;
	while (i < len)
	{
		if (token[len] == CL_SQUAR)
		{
			while  (i != len && token[len] != OP_SQUAR)
				len--;
		}
		tmp = token[len];
		token[len] = token[i];
		token[i] = tmp;
		len--;
		i++;
	}
	return (token);
}
