/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:52:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/18 12:17:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_H
# define CAST_H

# include <stdlib.h>

void	ft_cast_nbr(intmax_t *__restrict__ nb) __attribute__
		((nonnull));

void	ft_cast_unbr(uintmax_t *__restrict__ nb) __attribute__
		((nonnull));

#endif
