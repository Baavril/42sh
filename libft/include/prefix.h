/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:27:45 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/19 18:12:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREFIX_H
# define PREFIX_H

# include <locale.h>

typedef struct	s_prefi
{
	char *__restrict__			prefix;
	char *__restrict__			ch_base;
	struct lconv *__restrict__	lc;
	unsigned short			len;
	unsigned short			base:5;
	unsigned short			size:2;
	_Bool					neg:1;
}				t_prefix;

extern t_prefix	g_prefix;

void			reset_prefix(void);

#endif
