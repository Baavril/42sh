/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement_shellvar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:04:10 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/08 10:04:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell_variables.h"
#include "parser_utils_shvar.h"

/* expansion like module to get assignement in tokens or str ? */

int     assign_variable(char *str)
{
    char *value;
    char *name;
    int ret;

    if (!str)
        return (e_invalid_input);
    ret = is_format_legit(str);
    if (ret == ISLEGIT)
    {
        value = get_value(str);
        if (value)
        {
            if ((size_t)(value - str))
            {
                name = ft_strndup(str, (value - str - 1));
                ft_setenv(name, value, 1); /* using setenv as a test */
                ft_memdel((void**)&name);
            }
        }
    }
    else if (ret == HASINDEX)
    {
      /*  ft_printf("> %llu\n", get_index(str));*/
        return (e_success);
    }
    return (e_success);
}
