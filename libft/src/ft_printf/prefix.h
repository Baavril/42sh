/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:27:45 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:13:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREFIX_H
# define PREFIX_H

# include <locale.h>

typedef struct				s_prefix
{
	char *restrict			prefix;
	char *restrict			ch_base;
	struct lconv *restrict	lc;
	unsigned short			len;
	unsigned short			base:5;
	unsigned short			size:2;
	_Bool					neg:1;
}							t_prefix;

extern t_prefix				g_prefix;

void						reset_prefix(void);

#endif
