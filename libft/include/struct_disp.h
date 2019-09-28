/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_disp.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:49:00 by abarthel          #+#    #+#             */
/*   Updated: 2019/03/15 10:08:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_DISP_H
# define STRUCT_DISP_H

typedef struct	s_specifier
{
	char	type;
	void	*(*f)();
}				t_specifier;

#endif
