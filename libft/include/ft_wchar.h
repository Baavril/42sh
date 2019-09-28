/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:19:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/19 17:08:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WCHAR_H
# define FT_WCHAR_H

# include <stdlib.h>

int		ft_wcscmp(const wchar_t *s1, const wchar_t *s2) __attribute__
		((nonnull(1,2)));

int		ft_fputwc(wchar_t wc, int fd);

int		ft_fputws(const wchar_t *__restrict__ ws, int fd);

int		ft_putwchar(wchar_t wc);

int		ft_fwprintf(int fd, const wchar_t *__restrict__ format, ...);

int		ft_fputwcbits(wchar_t c, int fd);

int		ft_fputwsbits(const wchar_t *__restrict__ ws, int fd);

int		ft_putwstr(const wchar_t *__restrict__ ws);

int		ft_putwcbits(wchar_t c);

size_t	ft_wcslen(const wchar_t *ws);

wchar_t	*ft_wcscpy(wchar_t *ws1, const wchar_t *ws2) __attribute__
		((nonnull(1,2)));

int		ft_ewcwidth(wchar_t ws);

int		ft_ewcswidth(const wchar_t *__restrict__ pwcs);

int		ft_ewcsnwidth(const wchar_t *__restrict__ pwcs, size_t n);

#endif
