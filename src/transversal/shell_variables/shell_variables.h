/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:48:01 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/03 16:46:35 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_VARIABLES_H
# define SHELL_VARIABLES_H

typedef struct	s_shevar
{
	char		*str;
	char		*name;
	char		*value;
	int		expt;
	int		set;
}		t_shevar;

#endif
