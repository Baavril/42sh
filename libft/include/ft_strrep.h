/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:40:57 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 19:41:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRREP_H
# define FT_STRREP_H

struct			s_strrep
{
	const char	*content;
	const char	*expansion;
	char		*dst;
	char		*cpy;
	char		*ptr;
	char		*expansion_cpy;
	char		*content_cpy;
};

#endif
