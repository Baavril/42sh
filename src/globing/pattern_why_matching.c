/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_why_matching.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

char *ft_strwhy(char *token, char *match, int flag)
{
	int i;
	int len;
	int lim;
	char *ret;

	i = 0;
	lim = 0;
	if ((len = (int)ft_strlen(token) - (int)ft_strlen(match)) <= 0)
		return (ft_strdup(EMPTY_STR));
	if (flag == OPERCENT_EXP)
		if (len > 0)
			return (ret = ft_strndup(token, len));
	if (len > 0)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		lim = ft_strlen(match);
	}
	else
		return (token);
	while (i < len)
		ret[i++] = token[lim++];
	ret[i] = '\0';
	return (ret);
}
