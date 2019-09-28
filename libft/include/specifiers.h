/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:44:58 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/18 14:28:12 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECIFIERS_H
# define SPECIFIERS_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

void	ft_chr(wchar_t wc);

void	ft_wchr(wchar_t wc);

void	ft_str(void *__restrict__ str);

void	ft_wstr(void *__restrict__ wcs);

void	ft_n(int *__restrict__ ptr);

void	ft_nbr(intmax_t nb);

void	ft_upnbr(intmax_t nb);

void	ft_unbr(uintmax_t nb);

void	ft_upunbr(uintmax_t nb);

void	ft_lhexa(uintmax_t nb);

void	ft_uhexa(uintmax_t nb);

void	ft_octal(uintmax_t nb);

void	ft_upoc(uintmax_t nb);

void	ft_b(uintmax_t nb);

void	ft_ld(intmax_t nb);

void	ft_lo(uintmax_t nb);

void	ft_p(void *__restrict__ ptr);

void	ft_y(unsigned short value);

void	ft_double(va_list ap);

#endif
