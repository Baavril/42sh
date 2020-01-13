/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:00:51 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:16:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PRS_H
# define FT_PRINTF_PRS_H

# include <stdarg.h>

int	printf_prs(const char *restrict format, va_list ap);

#endif
