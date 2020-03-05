/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolvepath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:47:47 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:26:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_errno.h"
#include "libft.h"

static void	clean_end(char *str)
{
	char	*beg;

	beg = str;
	while (*str)
		++str;
	if ((str - beg) > 1)
	{
		if (str[-1] == '/')
			str[-1] = '\0';
	}
	else if ((str - beg) == 0)
	{
		*str = '/';
		*(str + 1) = '\0';
	}
}

static void	clean_start(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	(void)i;
	while ((ptr = ft_strstr(str, "//")))
	{
		ft_memmove(ptr, (ptr + 1), ft_strlen((ptr + 1)));
		while (*(ptr + 1))
			++ptr;
		while (*ptr)
		{
			*ptr = '\0';
			++ptr;
		}
	}
}

static void	currentdir_trim(char *str)
{
	char	*ptr;

	while ((ptr = ft_strstr(str, ".")))
	{
		if (*(ptr + 1) == '/')
			ft_memmove(ptr, (ptr + 1), ft_strlen((ptr + 1)));
		while (*(ptr + 1))
			++ptr;
		while (*ptr)
		{
			*ptr = '\0';
			++ptr;
		}
	}
}

static void	previousdir_res(char *str)
{
	char	*ptr;
	char	*next;
	int		i;

	i = 0;
	while ((ptr = ft_strstr(str, "..")))
	{
		next = ptr + 2;
		ptr -= 2;
		while (ptr > str && *ptr != '/')
			--ptr;
		if (ptr < str)
			ptr = str;
		i = ft_strlen(next);
		ft_memmove(ptr, next, i + 1);
	}
}

char		*ft_resolvepath(char *str)
{
	if (!str || *str != '/')
	{
		g_errno = E_EINVAL;
		return (NULL);
	}
	clean_start(str);
	previousdir_res(str);
	clean_start(str);
	currentdir_trim(str);
	clean_start(str);
	clean_end(str);
	return (str);
}
