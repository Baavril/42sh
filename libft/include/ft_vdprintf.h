/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:51:51 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 15:08:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VDPRINTF_H
# define FT_VDPRINTF_H

# include <stdarg.h>

int	ft_vdprintf(int fd, const char *restrict format, va_list ap);

#endif
