/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:37:02 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/12 13:56:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

char				*g_input;

static size_t		ft_new_input_len(void)
{
	size_t		i;
	size_t		len;
	_Bool		trig;	

	i = 0;
	len = 0;
	trig = 0;
	while (g_input[i])
	{
		if (g_input[i] == '#')
			trig = 1;
		if (!trig)
			++len;
		if (g_input[++i] == '\n')
			trig = 0;
	}
	return (len);
}


int					ft_trim_comment(void)
{
	size_t		i;
	size_t		j;
	_Bool		trig;	
	char		*new_input;

	i = 0;
	j = ft_new_input_len();
	if (!(new_input = ft_strnew(j)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (1);
	}
	j = 0;
	while (g_input[i])
	{
		if (g_input[i] == '#')
			trig = 1;
		if (!trig)
			new_input[j++] = g_input[i];
		if (g_input[++i] == '\n')
			trig = 0;
	}
	ft_strdel(&g_input);
	g_input = new_input;
	return (0);
}
