/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:09:16 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:47:13 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*search_prompt_intro(t_cursor *cursor)
{
	char *tmp;

	tmp = NULL;
	if (!cursor->match_ret)
	{
		tmp = ft_strdup("(reverse-i-search)`");
		return (tmp);
	}
	tmp = ft_strdup("(failed reverse-i-search)`");
	return (tmp);
}

size_t	search_prompt(t_cursor *cursor, char *buff)
{
	char	*intro;
	char	*outro;
	char	*tmp;
	int		len;

	len = 0;
	tmp = (!*buff) ? ft_strdup("") : ft_strdup(buff);
	intro = search_prompt_intro(cursor);
	outro = ft_strdup("': ");
	cursor->prompt = ft_strnjoinfree(3, intro, tmp, outro);
	len = ft_strlen(cursor->prompt);
	return (len);
}
