/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_get.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:24:17 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/17 10:51:07 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRS_GET_H
# define PRS_GET_H

# include <stdarg.h>

void	get_precision(const char *__restrict__ format, va_list ap);

void	get_flags(const char *__restrict__ format
		, _Bool *__restrict__ specifier);

_Bool	get_modifier(const char *__restrict__ format);

void	ft_get_width_or_dollar(const char *__restrict__ str
		, _Bool dot);

#endif
