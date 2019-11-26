/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"
#include "expansions.h"
#include "jcont.h"

static char	*get_retval(const char *str)
{
	char	*value;

	(void)str;
	value = ft_itoa(g_retval);
	return (value);
}

static char	*get_content(const char *str)
{
	char	*content;
	char	*cpy;

	content = ft_getenv(str);
	if (content)
		cpy = ft_strdup(content);
	else
		cpy = NULL;
	return (cpy);
}

const struct s_param	g_param[] =
{
	{"?", &get_retval},
/*	{"$", NULL},
	{"@", NULL},
*/	{"", &get_content}
};

static int	parameter_dispacther(char **content, const char *str)
{
	int	i;

	i = 0;
	while (*(g_param[i].pname))
	{
		if (!ft_strcmp(g_param[i].pname, str))
			break;
		++i;
	}
	if (!*(g_param[i].pname))
	{
		if (is_valid_param(str))
			return (e_bad_substitution);
	}
	*content = g_param[i].g(str);
	return (e_success);
}

int	getenv_content(char **content, char *str, const char *closetag)
{
	size_t	len;
	int	ret;
	char	c;

	ret = e_success;
	if (!*closetag && *(str - 1) == '$' && !is_a_valid_chr(*str) && *str != '?')
	{
		*content = ft_strdup("$");
		return (ret);
	}
	len = ft_varlen(str, closetag);
	if (!len)
		return (e_bad_substitution);
	c = str[len];
	str[len] = '\0';
	ret = parameter_dispacther(content, str);
	str[len] = c;
	return (ret);
}
