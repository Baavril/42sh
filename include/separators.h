/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:51:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 11:54:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATORS_H
# define SEPARATORS_H

struct	s_separators
{
	char	*sep;
};

int	unglue_sep(char **input);

#endif
