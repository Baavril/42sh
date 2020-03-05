/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:49:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:17:29 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <stdlib.h>

#include "prs_struct.h"
#include "libft.h"

extern t_ret		g_ret;
extern _Bool		g_error;

void				ft_expand_ret(int size)
{
	void *restrict	new_ret;

	g_ret.max += size < 1024 ? 1024 : size;
	if (!(new_ret = (char*)ft_memalloc(sizeof(char) * g_ret.max + 1)))
	{
		g_error = 1;
		return ;
	}
	else
	{
		if (g_ret.i > -1)
			ft_memcpy(new_ret, g_ret.ret, g_ret.i + 1);
		ft_memdel((void**)&g_ret.ret);
		g_ret.ret = (char*)new_ret;
	}
}
