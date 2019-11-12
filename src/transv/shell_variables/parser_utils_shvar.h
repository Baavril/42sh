/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_shvar.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:54:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/08 17:54:35 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_SHVAR_H
# define PARSER_UTILS_SHVAR_H

#include <stdint.h>

# define HASINDEX 2
# define ISLEGIT 1
# define NOTLEGIT 0

int         is_format_legit(const char *input);
char        *get_value(char *str);
_Bool       contains_array_subscript(char *str);
uint64_t    get_index(char *str);
char    	*get_name(char *str);


struct s_uint63
{
	uint64_t	val:63;
};

struct s_assign
{
    char        *name;
    char        *value;
    uint64_t    index:63;
    _Bool       hasindex:1;
};


#endif
